#pragma once
#include <worldGenerator.h>
#include <multyPlayer/chunkSaver.h>
#include <multyPlayer/serverChunkStorer.h>
#include <thread>
#include <atomic>

struct Client;

struct ThreadPool
{
	ThreadPool() {};

	constexpr static int MAX_THREADS = 12;

	int currentCounter = 0;
	
	std::thread threads[MAX_THREADS] = {};
	std::atomic_bool running[MAX_THREADS] = {};
	std::atomic_bool threIsWork[MAX_THREADS] = {};
	std::deque<std::atomic<bool>> taskTaken;


	void setThreadsNumber(int nr, void(*worker)(int, ThreadPool&));

	void setThrerIsWork();

	void waitForEveryoneToFinish();

	void cleanup();
};


void closeThreadPool();

int getThredPoolSize();

void splitUpdatesLogic(float tickDeltaTime,
	int tickDeltaTimeMs,
	std::uint64_t currentTimer,
	ServerChunkStorer &chunkCache, unsigned int seed,
	std::unordered_map<std::uint64_t, Client> &clients,
	WorldSaver &worldSaver, std::vector<ServerTask> &waitingTasks,
	Profiler &serverProfiler
);




