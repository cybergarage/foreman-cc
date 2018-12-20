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

////////////////////////////////////////////////
//  HttpClient
////////////////////////////////////////////////

HttpClient::HttpClient()
{
}

////////////////////////////////////////////////
//  ~HttpClient
////////////////////////////////////////////////

HttpClient::~HttpClient()
{
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
  CURL* curl;
  CURLcode res;

  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, uri.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, HttpClient::curl_response_reader);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&content);

    res = curl_easy_perform(curl);
    /* always cleanup */
    curl_easy_cleanup(curl);
    if (res == CURLE_OK)
      return true;
  }
  return false;
}
