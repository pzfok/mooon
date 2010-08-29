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
#ifndef MYLOG_H
#define MYLOG_H
#include "util/util_config.h"
UTIL_NAMESPACE_BEGIN

/**
  * 日志接口
  */
class ILogger
{
public:
    /** 空虚拟析构函数，以屏蔽编译器告警 */
    virtual ~ILogger() {}

    virtual bool enabled_debug() = 0;
    virtual bool enabled_info() = 0;
    virtual bool enabled_warn() = 0;
    virtual bool enabled_error() = 0;
    virtual bool enabled_fatal() = 0;
    virtual bool enabled_trace() = 0;

    virtual void log_debug(const char* format, ...) = 0;
    virtual void log_info(const char* format, ...)  = 0;
    virtual void log_warn(const char* format, ...)  = 0;
    virtual void log_error(const char* format, ...) = 0;
    virtual void log_fatal(const char* format, ...) = 0;
    virtual void log_trace(const char* format, ...) = 0;
};

//////////////////////////////////////////////////////////////////////////
// 日志宏，方便记录日志
extern ILogger* g_logger; // 只是声明，不是定义，不能赋值哦！

#define MYLOG_DEBUG(format, ...) \
do { \
	if (NULL == util::g_logger) \
		printf(format, ##__VA_ARGS__); \
	else if (util::g_logger->enabled_debug()) \
		util::g_logger->log_debug(format, ##__VA_ARGS__); \
} while(false)

#define MYLOG_INFO(format, ...) \
do { \
	if (NULL == util::g_logger) \
		printf(format, ##__VA_ARGS__); \
	else if (util::g_logger->enabled_info()) \
		util::g_logger->log_info(format, ##__VA_ARGS__); \
} while(false)

#define MYLOG_WARN(format, ...) \
do { \
	if (NULL == util::g_logger) \
		printf(format, ##__VA_ARGS__); \
	else if (util::g_logger->enabled_warn()) \
		util::g_logger->log_warn(format, ##__VA_ARGS__); \
} while(false)

#define MYLOG_ERROR(format, ...) \
do { \
	if (NULL == util::g_logger) \
		printf(format, ##__VA_ARGS__); \
	else if (util::g_logger->enabled_error()) \
		util::g_logger->log_error(format, ##__VA_ARGS__); \
} while(false)

#define MYLOG_FATAL(format, ...) \
do { \
	if (NULL == util::g_logger) \
		printf(format, ##__VA_ARGS__); \
	else if (util::g_logger->enabled_fatal()) \
		util::g_logger->log_fatal(format, ##__VA_ARGS__); \
} while(false)

#define MYLOG_TRACE(format, ...) \
do { \
	if (NULL == util::g_logger) \
		printf(format, ##__VA_ARGS__); \
	else if (util::g_logger->enabled_trace()) \
		util::g_logger->log_trace(format, ##__VA_ARGS__); \
} while(false)

UTIL_NAMESPACE_END
#endif // MYLOG_H
