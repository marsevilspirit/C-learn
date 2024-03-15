#include <iostream>
#include <string>
#include "account.pb.h" // 导入生成的 Protocol Buffers 文件
#include <hiredis/hiredis.h>

using namespace std;

int main() {
    // 连接到 Redis 服务器
    redisContext* redis = redisConnect("127.0.0.1", 6379);
    if (redis == NULL || redis->err) {
        if (redis) {
            cout << "Error: " << redis->errstr << endl;
            redisFree(redis);
        } else {
            cout << "Failed to connect to Redis server." << endl;
        }
        return 1;
    }

    // 名称
    string name = "alice";

    // 构造 Redis 命令
    string redis_command = "GET user:" + name;

    // 发送 Redis 命令并获取响应
    redisReply* reply = (redisReply*)redisCommand(redis, redis_command.c_str());
    if (reply == NULL) {
        cout << "Failed to execute Redis command." << endl;
        redisFree(redis);
        return 1;
    }

    // 检查响应类型
    if (reply->type != REDIS_REPLY_STRING) {
        cout << "No data found for user: " << name << endl;
        freeReplyObject(reply);
        redisFree(redis);
        return 1;
    }

    // 从响应中提取序列化数据
    string serialized_data = reply->str;

    // 释放响应对象
    freeReplyObject(reply);

    // 反序列化数据
    Account account;
    if (!account.ParseFromString(serialized_data)) {
        cerr << "Failed to parse serialized data." << endl;
        redisFree(redis);
        return 1;
    }

    // 提取信息并打印
    cout << "Name: " << account.username() << endl;
    cout << "Password: " << account.password() << endl;
    cout << "Email: " << account.email() << endl;

    // 断开与 Redis 的连接
    redisFree(redis);

    return 0;
}

