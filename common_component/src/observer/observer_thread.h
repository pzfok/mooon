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
#ifndef OBSERVER_THREAD_H
#define OBSERVER_THREAD_H
#include "sys/thread.h"
#include "util/util_config.h"
MY_NAMESPACE_BEGIN

class CObserverManager;
class CObserverThread: public sys::CThread
{
public:
	CObserverThread(CObserverManager* observer_manager);
	void stop();

private: // override
	virtual void run();

private:
	volatile bool _stop; /** �Ƿ��˳��߳� */
	CObserverManager* _observer_manager;
};

MY_NAMESPACE_END
#endif // OBSERVER_THREAD_H