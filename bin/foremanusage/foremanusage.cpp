/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno
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
  std::cout << "Usage : " << PROGRAM_NAME << " <memstore> <type> <hour>" << std::endl;
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

  Foreman::Metric::Store* store = nullptr;
  std::string storeType = argv[1];
  if (storeType.compare("matrix") == 0)
    store = new Foreman::Metric::MatrixStore();
  else if (storeType.compare("ringmap") == 0)
    store = new Foreman::Metric::RingMapStore();
  else if (storeType.compare("narrowtable") == 0)
    store = new Foreman::Metric::NarrowTableStore();
  else if (storeType.compare("tsmap") == 0)
    store = new Foreman::Metric::BeringeiStore();
  if (!store) {
    usage();
    std::cout << "Unknown Store Type : " << storeType << std::endl;
    return EXIT_FAILURE;
  }

  std::string recordTypeStr = argv[2];
  Foreman::BenchmarkControllerRecordType recordType;
  if (recordTypeStr.compare("random") == 0)
    recordType = Foreman::BenchmarkControllerRandomRecordType;
  else if (recordTypeStr.compare("periodic") == 0)
    recordType = Foreman::BenchmarkControllerPeriodicRecordType;
  else if (recordTypeStr.compare("sporadic") == 0)
    recordType = Foreman::BenchmarkControllerSporadicRecordType;
  else if (recordTypeStr.compare("constant") == 0)
    recordType = Foreman::BenchmarkControllerConstantRecordType;
  else {
    usage();
    std::cout << "Unknown Record Type : " << recordTypeStr << std::endl;
    return EXIT_FAILURE;
  }

  long retentionPeriodHour = atol(argv[3]);
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

  benchmark.initialize(store, retentionPeriodHour);

  lastUsage = get_memory_usages();
  benchmark.insertRecords(store, retentionPeriodHour, beginTs, endTs, recordType);
  long memUsage = get_memory_usages() - lastUsage;

  std::cout << storeType << "/" << recordTypeStr << "/" << retentionPeriodHour << "," << memUsage << std::endl;

  delete store;

  return EXIT_SUCCESS;
}
