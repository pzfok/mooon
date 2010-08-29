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
 * Author: JianYi, eyjian@qq.com or eyjian@gmail.com
 */
#ifndef SYS_MMAP_H
#define SYS_MMAP_H
#include "sys/syscall_exception.h"
SYS_NAMESPACE_BEGIN

typedef struct
{
    int fd;      /** 如果是通过fd映射的，则为文件句柄的负值，否则为mmap操作时打开的文件句柄 */
    void* addr;  /** 文件映射到内存的地址，如果文件未被映射到内存则为NULL */
    size_t len;  /** 文件大小 */
}mmap_t;

/** 内存文件映射操作类 */
class CMMap
{
public:
    /** 将指定fd对应的文件映射到内存
      * @fd: 文件句柄，调用者需要负责关闭此句柄，mmap_t结构的fd成员为它的负值
      * @size_max: 最大可映射字节数，超过此大小的文件将不会被映射到内存，mmap_t结构的addr成员将为NULL
      * @return: 返回指向mmap_t结构的指针，返回值总是不会为NULL
      * @exception: 出错抛出CSyscallException异常
      */
    static mmap_t* map(int fd, uint64_t size_max=0);

    /** 将指定文件名对应的文件映射到内存
      * @filename: 文件名，mmap_t结构的fd成员为打开此文件的句柄
      * @size_max: 最大可映射字节数，超过此大小的文件将不会被映射到内存，mmap_t结构的addr成员将为NULL
      * @return: 返回指向mmap_t结构的指针，返回值总是不会为NULL
      * @exception: 出错抛出CSyscallException异常
      */
    static mmap_t* map(const char* filename, uint64_t size_max=0);

    /** 释放已创建的内存映射，如果是通过指定文件名映射的，则关闭在mmap中打开的句柄
      * @ptr: 已创建的内存映射      
      */
    static void unmap(mmap_t* ptr);

    static void sync_flush(mmap_t* ptr, size_t offset=0, size_t length=0, bool invalid=false);
    static void async_flush(mmap_t* ptr, size_t offset=0, size_t length=0, bool invalid=false);

private:
    static mmap_t* do_map(int fd, uint64_t size_max, bool byfd);
};

SYS_NAMESPACE_END
#endif // SYS_MMAP_H
