#ifndef _READER_JSON_HPP_
#define _READER_JSON_HPP_

#include <iostream>
#include <fstream>

#include "json\json.h"

enum jsonType {
    type,
    title,
    content,
    likes,
    dislikes,
    test
};

class ReaderJson {

    Json::Value root;
    Json::Reader reader;

public :
    void getJsonContent();
    void PrintJsonValue(const Json::Value& val) const;
    void loopThroughNode(const Json::Value& node) const;
};

void ReaderJson::PrintJsonValue(const Json::Value& val) const {
    if (val.isString()) {
        if (val.asString().c_str() == (const char*) jsonType::test)
        {
            printf("is string(%s) ", val.asString().c_str());
        }
        else
        {
            printf("default string(%s) ", val.asString().c_str());
        }
    }
    else if (val.isBool()) {
        printf("bool(%d) ", val.asBool());
    }
    else if (val.isInt()) {
        printf("int(%d) ", val.asInt());
    }
    else if (val.isUInt()) {
        printf("uint(%u) ", val.asUInt());
    }
    else if (val.isDouble()) {
        printf("double(%f) ", val.asDouble());
    }
    else
    {
        printf("unknown type=[%d] ", val.type());
    }
}

void ReaderJson::loopThroughNode(const Json::Value& node) const
{
    for (Json::Value::const_iterator itr = node.begin(); itr != node.end(); itr++)
    {
        Json::Value value = *itr;
        if (value.isArray()) {
            printf("%s \n\n", itr.key().asString().c_str());
            loopThroughNode(value);
        }
        else if (value.isObject()) {
            loopThroughNode(value);
        }
        else {
            PrintJsonValue(itr.key());
            PrintJsonValue(value);
            printf("\n");
        }
    }
}

void ReaderJson::getJsonContent() {
    std::ifstream json("./test.json", std::ifstream::in);

    if (reader.parse(json, root))
    {
        loopThroughNode(root);
    }
}

#endif //_READER_JSON_HPP_