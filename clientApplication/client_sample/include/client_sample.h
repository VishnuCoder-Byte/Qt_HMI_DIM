#ifndef CLIENT_SAMPLE_H
#define CLIENT_SAMPLE_H
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


class client_sample
{
    public:
        client_sample() :
        app_(vsomeip::runtime::get()->create_application()),
        payload_(vsomeip::runtime::get()->create_payload())
        //notify_thread_(std::bind(&client_sample::notify, this))
        {}

        bool init()
        {
            if (!app_->init()) {
            std::cout << "Couldn't initialize application" << std::endl;
            return false;
            }

                   app_->register_state_handler(
                std::bind(&client_sample::on_state_cbk, this,
                        std::placeholders::_1));




            // register a callback for responses from the service
            app_->register_message_handler(vsomeip::ANY_SERVICE,
            service_instance_id, vsomeip::ANY_METHOD,
            std::bind(&client_sample::on_message_cbk, this,
            std::placeholders::_1));

            std::set<vsomeip::eventgroup_t> its_groups;
            its_groups.insert(SAMPLE_EVENTGROUP_ID);
            payload_ = vsomeip::runtime::get()->create_payload();
        }

        void on_state_cbk(vsomeip::state_type_e _state)
        {
            if(_state == vsomeip::state_type_e::ST_REGISTERED)
            {
            // we are registered at the runtime now we can request the service
            // and wait for the on_availability callback to be called
            app_->request_service(service_id, service_instance_id);
            }
        }

        void on_message_cbk(const std::shared_ptr<vsomeip::message> &_response)
        {
            if(service_id == _response->get_service()
                && service_instance_id == _response->get_instance()
                && vsomeip::message_type_e::MT_RESPONSE
                        == _response->get_message_type()
                && vsomeip::return_code_e::E_OK == _response->get_return_code())
            {
            // Get the payload and print it
            std::shared_ptr<vsomeip::payload> pl = _response->get_payload();
            std::string resp = std::string(
                    reinterpret_cast<const char*>(pl->get_data()), 0,
                    pl->get_length());
            //LOG_INF("Received: %s", resp.c_str());
            std::cout<<"Data received "<<resp<<std::endl;
            // stop();
            }
        }


        void start() {
            app_->start();
        }

        //virtual ~server_sample();
        client_sample(const client_sample& other);
        ~client_sample() {}

    protected:

    private:
        std::shared_ptr<vsomeip::application> app_;
        std::shared_ptr<vsomeip::payload> payload_;
        std::thread notify_thread_;

};

#endif // CLIENT_SAMPLE_H
