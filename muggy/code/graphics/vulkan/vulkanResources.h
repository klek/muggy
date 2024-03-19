//********************************************************************
//  File:    vulkanResources.h
//  Date:    Mon, 18 Mar 2024: 23:42
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(VULKAN_RESOURCES_H)
#define VULKAN_RESOURCES_H

#include "vulkanCommon.h"

namespace muggy::graphics::vulkan
{
    struct image_init_info
    {
        VkDevice                device;
        VkImageType             imageType;
        uint32_t                width;
        uint32_t                height;
        VkFormat                format;
        VkImageTiling           tiling;
        VkImageUsageFlags       usageFlags;
        VkMemoryPropertyFlags   memoryFlags;
        bool                    createView;
        VkImageAspectFlags      viewAspectFlags;
    };

    bool createImage( const image_init_info* const initInfo, 
                      vulkan_image& image );
    bool createImageView( VkDevice device, 
                          VkFormat format, 
                          vulkan_image* image,
                          VkImageAspectFlags viewAspectFlags );
    void destroyImage( VkDevice device, vulkan_image* image );

    bool createFrameBuffer( VkDevice device,
                            vulkan_renderpass& renderPass,
                            uint32_t width,
                            uint32_t height,
                            uint32_t attachCount,
                            VkImageView* attachments,
                            vulkan_framebuffer& frameBuffer );
    void destroyFrameBuffer( VkDevice device, 
                             vulkan_framebuffer& frameBuffer );

} // namespace muggy::graphics::vulkan


#endif