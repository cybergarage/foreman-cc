/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

#include <sys/resource.h>
#include <sys/time.h>

#define PROGRAM_NAME "foramanusage"
#define FORMANCC_BENCHMARK_RETENSION_INTERVAL 60
#define FORMANCC_BENCHMARK_METRICS_COUNT 1000

#include "BenchmarkController.h"

void usage()
{
  std::cout << "Usage : " << PROGRAM_NAME << " <memstore> <hour>" << std::endl;
}

long get_memory_usages()
{
  struct rusage rusage;
  getrusage(RUSAGE_SELF, &rusage);
  return rusage.ru_maxrss;
}

void print_memory_usages(const std::string& header, long lastUsage)
{
  long usage = get_memory_usages();
  printf("%s : %ld\n", header.c_str(), (usage - lastUsage));
}

int main(int argc, char* argv[])
{
  if (argc < 3) {
    usage();
    return EXIT_FAILURE;
  }

  Foreman::MemStore* memStore = nullptr;
  std::string memStoreType = argv[1];
  if (memStoreType.compare("matrix") == 0)
    memStore = new Foreman::MatrixStore();
  else if (memStoreType.compare("ringmap") == 0)
    memStore = new Foreman::RingMapStore();
  else if (memStoreType.compare("narrowtable") == 0)
    memStore = new Foreman::NarrowTableStore();
  else if (memStoreType.compare("tsmap") == 0)
    memStore = new Foreman::TSmapStore();

  if (!memStore) {
    usage();
    std::cout << "Unknown MemStore Type : " << memStoreType << std::endl;
    return EXIT_FAILURE;
  }

  long retentionPeriodHour = atol(argv[2]);
  if (retentionPeriodHour <= 0) {
    usage();
    std::cout << "Invalid Retention Period Hour : " << retentionPeriodHour << std::endl;
    return EXIT_FAILURE;
  }

  time_t beginTs = 0, endTs = 0;
  long lastUsage = 0;

  Foreman::BenchmarkController benchmark;
  benchmark.setRetentionIntervel(FORMANCC_BENCHMARK_RETENSION_INTERVAL);
  benchmark.setMetricsCount(FORMANCC_BENCHMARK_METRICS_COUNT);

  benchmark.initialize(memStore, retentionPeriodHour);

  lastUsage = get_memory_usages();
  benchmark.insertRecords(memStore, retentionPeriodHour, beginTs, endTs);
  long memUsage = get_memory_usages() - lastUsage;

  std::cout << memStoreType << "/" << retentionPeriodHour << "," << memUsage << std::endl;

  delete memStore;

  return EXIT_SUCCESS;
}
