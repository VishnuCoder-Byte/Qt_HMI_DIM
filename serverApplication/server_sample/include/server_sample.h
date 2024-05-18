#ifndef SERVER_SAMPLE_H
#define SERVER_SAMPLE_H

#include <iostream>
#include <vsomeip/vsomeip.hpp>
#include <chrono>
#include <thread>
#include <mutex>

static vsomeip::service_t service_id = 0x1111;
static vsomeip::instance_t service_instance_id = 0x2222;
static vsomeip::method_t service_method_id = 0x3333;
#define SAMPLE_SERVICE_ID       0x1234
#define SAMPLE_INSTANCE_ID      0x5678
#define SAMPLE_METHOD_ID        0x0421

#define SAMPLE_EVENT_ID         0x8778
#define SAMPLE_GET_METHOD_ID    0x0001
#define SAMPLE_SET_METHOD_ID    0x0002

#define SAMPLE_EVENTGROUP_ID    0x4465

#define OTHER_SAMPLE_SERVICE_ID 0x0248
#define OTHER_SAMPLE_INSTANCE_ID 0x5422
#define OTHER_SAMPLE_METHOD_ID  0x1421

class server_sample
{
    public:
        server_sample():
        app_(vsomeip::runtime::get()->create_application()),
        payload_(vsomeip::runtime::get()->create_payload()),
        notify_thread_(std::bind(&server_sample::notify, this))
        {}

        bool init()
        {
            if (!app_->init()) {
            std::cout << "Couldn't initialize application" << std::endl;
            return false;
            }

            std::set<vsomeip::eventgroup_t> its_groups;
            its_groups.insert(SAMPLE_EVENTGROUP_ID);
            payload_ = vsomeip::runtime::get()->create_payload();
        }

        void notify()
        {

            while (true)
            {
                std::string str = "Hello World";
                std::vector<vsomeip::byte_t> pl_data(str.begin(), str.end());
                payload_->set_data(pl_data);
                app_->notify(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_EVENT_ID, payload_);
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                std::cout<<"data send"<<std::endl;

            }

        }

        void start() {
            app_->start();
        }

        //virtual ~server_sample();
        server_sample(const server_sample& other);

    protected:

    private:
        std::shared_ptr<vsomeip::application> app_;
        std::shared_ptr<vsomeip::payload> payload_;
        std::thread notify_thread_;
};

#endif // SERVER_SAMPLE_H
