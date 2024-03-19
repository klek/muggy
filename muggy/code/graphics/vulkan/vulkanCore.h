//********************************************************************
//  File:    vulkanCore.h
//  Date:    Thu, 07 Mar 2024: 16:58
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(VULKAN_CORE_H)
#define VULKAN_CORE_H

#include "vulkanCommon.h"

namespace muggy::graphics::vulkan::core
{
    bool initialize( void );
    void shutdown( void );

    bool createDevice( VkSurfaceKHR surface );
    bool createGraphicsCommand( uint32_t swapchainBufferSize );
    bool detectDepthFormat( VkPhysicalDevice physicalDevice );
    int32_t findMemoryIndex( uint32_t type, uint32_t flags );

    // Helper functions
    uint32_t getGraphicsFamilyQueueIndex( void );
    uint32_t getPresentationFamilyQueueIndex( void );
    VkFormat getDepthFormat( void );
    VkPhysicalDevice getPhysicalDevice( void );
    VkDevice getLogicalDevice( void );
    VkInstance getInstance( void );

    // Low-level functions for vulkan surfaces
    surface createSurface( platform::window window );
    void removeSurface( surface_id id );
    void resizeSurface( surface_id id, uint32_t width, uint32_t height );
    uint32_t getSurfaceWidth( surface_id id );
    uint32_t getSurfaceHeigth( surface_id id );
    void renderSurface( surface_id id /*, frame_info info*/ );

} // namespace muggy::graphics::vulkan::core


#endif