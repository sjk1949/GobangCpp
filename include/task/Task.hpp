#pragma once

class Application;

class Task
{
public:
    virtual ~Task() = default;
    virtual void execuate(Application& app) = 0;
};

class StartGameTask : public Task
{
public:
    void execuate(Application& app) override;
};

class ExitTask : public Task
{
public:
    void execuate(Application& app) override;
};