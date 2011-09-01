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
 * Author: eyjian@qq.com or eyjian@gmail.com
 */
#ifndef MOOON_DISPATCHER_CONFIG_H
#define MOOON_DISPATCHER_CONFIG_H
 #include <unistd.h>
#include <sys/log.h>

/**
  * ���빦�ܿ��ƺ�
  */
#define ENABLE_CONFIG_UPDATE     0  /** �Ƿ�������ʵʱ���¹��ܣ���ҪAgent֧�� */
#define ENABLE_LOG_STATE_DATA    0  /** �Ƿ�����¼״̬���ݹ��ܣ���ҪObserver֧�� */
#define ENABLE_REPORT_STATE_DATA 0  /** �Ƿ����ϱ�״̬���ݹ��ܣ���ҪAgent֧�� */

/***
  * dispatcherģ������ֿռ�����
  */
#define DISPATCHER_NAMESPACE_BEGIN  namespace dispatcher {
#define DISPATCHER_NAMESPACE_END                         }
#define DISPATCHER_NAMESPACE_USE using dispatcher;

#endif // MOOON_DISPATCHER_CONFIG_H