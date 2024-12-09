#pragma once
#include "framework/Core.h"
#include <functional>

namespace ly
{
    class Object;
    template<typename... Args>
    class Delegate
    {
        public:

            template<typename ClassName>
            void BindAction(weak<Object> obj_, void(ClassName::*callback_)(Args...))
            {
                std::function<bool(Args...)> callbackFunc_ = [obj_, callback_](Args... args_)->bool
                {
                    if(!obj_.expired())
                    {
                        (static_cast<ClassName*>(obj_.lock().get())->*callback_)(args_...);
                        return true;
                    }
                    return false;
                };

                mCallbacks.push_back(callbackFunc_);
            }

            void Broadcast(Args... args_)
            {
                for(auto iter = mCallbacks.begin(); iter != mCallbacks.end();)
                {
                    if((*iter)(args_...))
                    {
                        ++iter;
                    }
                    else
                    {
                        iter = mCallbacks.erase(iter);
                    }
                }
            }

        private:
        
            List<std::function<bool(Args...)>> mCallbacks;
    };
} // namespace ly
