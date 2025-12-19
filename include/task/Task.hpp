#pragma once

class Task
{
public:
    virtual ~Task() = default;
    virtual void execuate() = 0;
};

class StartGameTask : public Task
{
public:
    void execuate() override {};
};

class ExitTask : public Task
{
public:
    void execuate() override {};
};