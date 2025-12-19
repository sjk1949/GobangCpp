#include "task/Task.hpp"

#include "app/Application.hpp"

void StartGameTask::execuate(Application& app) {
    app.startGame();
}

void ExitTask::execuate(Application& app) {
    app.exit();
}