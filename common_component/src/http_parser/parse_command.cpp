/**
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Author: JianYI, eyjian@qq.com
 */
#include "parse_command.h"
#include "util/string_util.h"
MY_NAMESPACE_BEGIN

//////////////////////////////////////////////////////////////////////////
// CParseCommand

CParseCommand::CParseCommand()
	:_http_event(NULL)
{    
	reset();
}

CParseCommand::~CParseCommand()
{
}

void CParseCommand::reset()
{
	_next_command = NULL;
}

//////////////////////////////////////////////////////////////////////////
// CNonNameValuePairCommand

CNonNameValuePairCommand::CNonNameValuePairCommand()
{
	reset();
}

void CNonNameValuePairCommand::reset()
{
	CParseCommand::reset();
	_begin = NULL;
	_end = NULL;
}

//  GET, POST, HEAD
util::TReturnResult CNonNameValuePairCommand::do_execute(const char* buffer, int& offset, char endchar, bool (IHttpEvent::*on_xxx)(const char*, const char*))
{
    const char* iter = buffer;
    
    for (;;)
    {
        if ('\0' == *iter) break;
        if (NULL == _begin) 
		{
            iter = util::CStringUtil::skip_spaces(iter);
			if (NULL == iter) // �ո����
			{
                get_http_event()->on_error("too much spaces in the first line");
				return return_result(util::rr_error);
			}
			
			if ('\0' == *iter) break;
			_begin = iter;
            ++iter;
		}
        
        if ('\0' == *iter) break;
        
        if (endchar == *iter)
        {
            _end = iter;
            if (!(get_http_event()->*on_xxx)(_begin, _end)) return return_result(util::rr_error);
            
            ++iter; // �ո�
			offset = iter-buffer;
            return return_result(util::rr_finish);
        }

        ++iter;
    }

	offset = iter-buffer;
    return util::rr_continue;
}

util::TReturnResult CMethodCommand::execute(const char* buffer, int& offset)
{	
    return do_execute(buffer, offset, ' ', &IHttpEvent::on_method);
}

util::TReturnResult CURLCommand::execute(const char* buffer, int& offset)
{	
    return do_execute(buffer, offset, ' ', &IHttpEvent::on_url);
}

util::TReturnResult CVersionCommand::execute(const char* buffer, int& offset)
{	
    return do_execute(buffer, offset, '\r', &IHttpEvent::on_version);
}

//////////////////////////////////////////////////////////////////////////
// CNameValuePairCommand

CNameValuePairCommand::CNameValuePairCommand()
{        
	reset();
}

void CNameValuePairCommand::reset()
{
	CParseCommand::reset();
    _ignore_colon = false;
    _name_begin   = NULL;
    _name_end     = NULL;
    _value_begin  = NULL;
    _value_end    = NULL;
}

// ÿһ����\n��ͷ����\r��β
util::TReturnResult CNameValuePairCommand::execute(const char* buffer, int& offset)
{
    const char* iter = buffer;

    for (;;)
    {
        if ('\0' == *iter) break;
        if (NULL == _name_begin)
        {
            // GET / HTTP/1.1\r\n
            // F1\r\n
            // F2\r\n
            // \r\n
            if (*iter != '\n')
            {
                get_http_event()->on_error("NV pair not started with '\\n'");
                return return_result(util::rr_error);            
            }
            
            ++iter;
            if ('\0' == *iter) break;            
            if ('\r' == *iter) // ��\n\r��ͷ����ʾ��ͷ����
            {
                ++iter;
                offset = iter-buffer;
                return return_result(util::rr_finish);
            }
            
            _name_begin = iter;
            ++iter;
        }
        else if ((NULL == _value_begin) && (_name_end != NULL))
        {
            iter = util::CStringUtil::skip_spaces(iter);
            if (NULL == iter)
            {
                get_http_event()->on_error("too much spaces in NV pair");
                return return_result(util::rr_error);
            }

            if ('\0' == *iter) break;
            _value_begin = iter;
            ++iter;
        }

        if ('\0' == *iter) break;

        if ('\r' == *iter)
        {
            _value_end = iter;
            if (!get_http_event()->on_name_value_pair(_name_begin, _name_end, _value_begin, _value_end))
                return return_result(util::rr_error);
            
            // ׼����һ�����ֶԵĽ���
            _name_begin  = NULL;
            _name_end    = NULL;
            _value_begin = NULL;
            _value_end   = NULL;
            _ignore_colon = false;
        }
        else if ((':' == *iter) && !_ignore_colon)
        {
            _name_end = iter;     
            _ignore_colon = true;
        }

        ++iter;
    }

    offset = iter-buffer;
    return return_result(util::rr_continue);
}

util::TReturnResult CHeadEndCommand::execute(const char* buffer, int& offset)
{
    if ('\0' == *buffer) return util::rr_continue;
    if (*buffer != '\n')
    {
        get_http_event()->on_error("http head not ended with '\\n'");
        return return_result(util::rr_error);
    }

    offset = 1;
    return return_result(util::rr_finish);
}

MY_NAMESPACE_END