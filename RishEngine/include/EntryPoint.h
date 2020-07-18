/**
 * @file EntryPoint.h
 * @brief The Entry Point of RishEngine Applications
 * @author roy4801 (roy@rish.com.tw)
 */
#pragma once

extern rl::Application* rl::CreateApplication();

int main(int argc, char **argv)
{
    setvbuf(stdin, nullptr, _IONBF, 0);
    setvbuf(stdout, nullptr, _IONBF, 0);
    //
    rl::Logger::Init();
    rl::VFS::Init();

    RL_CORE_INFO("Initializating the RishEngine");
    auto app = rl::CreateApplication();

    RL_CORE_INFO("RishEngine is running");
    app->run();

    RL_CORE_INFO("Shutdowning the RishEngine");
    delete app;

    rl::VFS::ShutDown();
    RL_CORE_INFO("Goodbye");
}