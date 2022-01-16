#pragma once






#include <stdint.h>

static VkPipeline graphicsPipeline;
static VkCommandPool commandPool;

namespace Pipeline
{
    static void createRenderPasses();
    static void createGraphicsPipelineLayout();
    static void createCommandPool();
};




 static  VkVertexInputBindingDescription* getVertexInputBindingDescription()
    {
         VkVertexInputBindingDescription a {
                .binding=0,
//                    .stride(vertices.length/2)
//                    .stride(vertices.length/VERT_SIZE+1)
                .stride=32,
                .inputRate=VK_VERTEX_INPUT_RATE_VERTEX
        };
        return &a;
    }

//     static VkVertexInputAttributeDescription*  getAttributeDescriptions()
//     {

//         VkVertexInputAttributeDescription attributeDescriptions[3];

//         // Position
//         VkVertexInputAttributeDescription* posDescription = &attributeDescriptions[0];
//         posDescription->binding=0;
//         posDescription->location=0;
//         posDescription->format=VK_FORMAT_R32G32B32_SFLOAT;
//         posDescription->offset=OFFSET_POS;

//         // Color
//         VkVertexInputAttributeDescription* colorDescription = &attributeDescriptions[1];
//         colorDescription->binding=0;
//         colorDescription->location=1;
//         colorDescription->format=VK_FORMAT_R32G32B32_SFLOAT;
//         colorDescription->offset=OFFSETOF_COLOR;

//         // Texture coordinates
//         VkVertexInputAttributeDescription *texCoordsDescription = attributeDescriptions[2];
//         texCoordsDescription->binding=0;
//         texCoordsDescription->location=2;
//         texCoordsDescription->format=VK_FORMAT_R32G32_SFLOAT;
//         texCoordsDescription->offset=OFFSETOF_TEXTCOORDS;

// //            memFree(attributeDescriptions);

//         return attributeDescriptions;
//     }

    