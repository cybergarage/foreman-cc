/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <curl/curl.h>
#include <foreman/net/HttpClient.h>

using namespace Foreman;

ssize_t Foreman::HttpClient::InstanceCount = 0;

////////////////////////////////////////////////
//  HttpClient
////////////////////////////////////////////////

HttpClient::HttpClient()
{
  initialize();
}

void HttpClient::initialize()
{
  lock();

  if (InstanceCount <= 0) {
    curl_global_init(CURL_GLOBAL_ALL);
  }
  InstanceCount++;

  unlock();
}

////////////////////////////////////////////////
//  ~HttpClient
////////////////////////////////////////////////

HttpClient::~HttpClient()
{
  finalize();
}

void HttpClient::finalize()
{
  lock();

  InstanceCount--;
  if (InstanceCount <= 0) {
    curl_global_cleanup();
  }

  unlock();
}

////////////////////////////////////////////////
//  HttpClient::encode
////////////////////////////////////////////////

bool HttpClient::encode(const std::string& str, std::string& encordedStr)
{
  CURL* curl = curl_easy_init();
  if (!curl)
    return false;

  char* ret = curl_easy_escape(curl, str.c_str(), (int)str.size());
  if (ret) {
    encordedStr = ret;
    curl_free(ret);
  }

  curl_easy_cleanup(curl);

  return (ret != NULL) ? true : false;
}

////////////////////////////////////////////////
//  HttpClient::get
////////////////////////////////////////////////

/* Curl gets the response in chunks, so we need to collect them into a single
 * string.
 */
size_t HttpClient::curl_response_reader(void* ptr, size_t size, size_t nmemb, std::string* s)
{
  size_t previous = s->size();
  s->append((char*)ptr, size * nmemb);
  return s->size() - previous;
}

bool HttpClient::get(const std::string& uri, std::string& content)
{
  CURL* curl = curl_easy_init();
  if (!curl)
    return false;

  curl_easy_setopt(curl, CURLOPT_URL, uri.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, HttpClient::curl_response_reader);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&content);

  CURLcode res = curl_easy_perform(curl);

  curl_easy_cleanup(curl);

  return (res == CURLE_OK) ? true : false;
}
