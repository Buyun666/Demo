#include <fstream>
#include <iostream>
#include "frame.pb.h"
 
int main() {
    // 创建Frames消息并添加多帧数据
    Frames frames;
    for (int i = 0; i < 10; ++i) {
        Frame* frame = frames.add_frames();
        frame->set_id(i);
        frame->set_data("Frame " + std::to_string(i));
    }
 
    // 序列化并写入文件
    {
        std::fstream output("frames.proto", std::ios::out | std::ios::binary);
        if (!frames.SerializeToOstream(&output)) {
            std::cerr << "Failed to write frames to disk." << std::endl;
            return 1;
        }
    }

    // 从文件读取并反序列化
    Frames read_frames;
    {
        std::fstream input("frames.proto", std::ios::in | std::ios::binary);
        if (!read_frames.ParseFromIstream(&input)) {
            std::cerr << "Failed to read frames from disk." << std::endl;
            return 1;
        }
        input.close();
    }
 
    // 输出读取的帧数据
    for (const Frame& frame : read_frames.frames()) {
        std::cout << "ID: " << frame.id() << ", Data: " << frame.data() << std::endl;
    }
 
    return 0;
}