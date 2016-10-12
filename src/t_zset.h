﻿/*
* Licensed to the Apache Software Foundation (ASF) under one
* or more contributor license agreements.  See the NOTICE file
* distributed with this work for additional information
* regarding copyright ownership.  The ASF licenses this file
* to you under the Apache License, Version 2.0 (the
* "License"); you may not use this file except in compliance
* with the License.  You may obtain a copy of the License at
*
*   http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing,
* software distributed under the License is distributed on an
* "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
* KIND, either express or implied.  See the License for the
* specific language governing permissions and limitations
* under the License.
*/

#ifndef T_ZSET_H
#define T_ZSET_H

#include "util/iobuffer.h"
#include "leveldb.h"
#include "t_hash.h"

class ZSetItem
{
public:
    ZSetItem(void) : score(0) {}
    ZSetItem(const ZSetItem& rhs) { *this = rhs;}
    ~ZSetItem(void) {}
    ZSetItem& operator=(const ZSetItem& rhs) {
        if (this != &rhs) {
            name = rhs.name;
            score = rhs.score;
        }
        return *this;
    }

    std::string name;
    double score;
};

typedef std::list<ZSetItem> ZSetItemList;

class TZSet : public THash
{
public:
    TZSet(LeveldbCluster* dbCluster, const std::string& name);
    ~TZSet(void);

    bool zadd(double score, const std::string &element);
    bool zrem(const std::string& element);
    bool zincrby(const std::string& element, double& num);
    int zrank(const std::string& element);
    int zrevrank(const std::string& element);
    bool zrange(int start, int stop, ZSetItemList* result);
    bool zrevrange(int start, int stop, ZSetItemList* result);
    bool zrangebyscore(double min_score, double max_score, ZSetItemList* result);
    bool zrevrangebyscore(double max_score, double min_score, ZSetItemList* result);
    int zcount(double min_score, double max_score);
    int zcard(void);
    bool zscore(const std::string& element, double* score);
    int zremrangebyrank(int start, int stop);
    int zremrangebyscore(double min_score, double max_score);

private:
    void query(ZSetItemList* result);
    bool transformIndex(int& start, int& stop, int maxsize);
};


#endif
