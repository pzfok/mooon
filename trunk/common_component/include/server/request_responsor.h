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
 * Author: jian yi, eyjian@qq.com
 */
#ifndef MOOON_SERVER_REQUEST_RESPONSOR_H
#define MOOON_SERVER_REQUEST_RESPONSOR_H
#include <util/util_config.h>
MOOON_NAMESPACE_BEGIN

class CALLBACK_INTERFACE IRequestResponsor
{
public:
    /** 空虚拟析构函数，以屏蔽编译器告警 */
    virtual ~IRequestResponsor() {}

    /** 复位状态 */
    virtual void reset() = 0;

    /** 是否发送一个文件 */
    virtual bool is_send_file() const = 0;
    
    /** 得到需要发送的大小 */
    virtual size_t get_size() const = 0;

    /** 得到从哪偏移开始发送 */
    virtual size_t get_offset() const = 0; 

    /** 得到文件句柄 */
    virtual int get_fd() const = 0;              

    /** 得到需要发送的数据 */
    virtual const char* get_buffer() const = 0;

    /***
      * 移动偏移
      * @offset: 本次发送的字节数
      */
    virtual void move_offset(size_t offset) = 0;

    /***
     * 包发送完后被回调
     * @return 如果返回util::handle_continue表示不关闭连接继续使用；
     *         如果返回util::handle_release表示需要移交控制权，
     *         返回其它值则关闭连接
     */
    virtual util::handle_result_t send_completed() = 0;
};

MOOON_NAMESPACE_END
#endif // MOOON_SERVER_REQUEST_RESPONSOR_H