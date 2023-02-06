#include "data.h"

ModelObjectsInfo getModelObjectsInfo() {
    using RenderChannel = ca::types::ModelView::Object::RenderChannel;

    return {
        .modelViews = {
            {
                .viewId = 1,
                .viewTypeName = "Building",
                .viewName = "Terminal",
                .createdAt = "2020-09-01T08:00:00+0800",
                .viewObjectList = {
                    {
                        .objectTypeID = 1,
                        .name = "stair",
                        .meshCounts = { 2000, 3000, 3000 },
                        .renderChannels = RenderChannel::Buffer | RenderChannel::Image
                    },
                    {
                        .objectTypeID = 2,
                        .name = "window",
                        .meshCounts = { 3000, 4000, 4000 },
                        .renderChannels = RenderChannel::Buffer
                    },
                    {
                        .objectTypeID = 3,
                        .name = "pool",
                        .meshCounts = { 100, 101 },
                        .renderChannels = RenderChannel::Buffer | RenderChannel::Window | RenderChannel::Image
                    },
                    {
                        .objectTypeID = 4,
                        .name = "pinball arcade",
                        .meshCounts = { 1000, 999 },
                        .renderChannels = RenderChannel::Buffer | RenderChannel::Image | RenderChannel::Printer
                    },
                },
            },
            {
                .viewId = 2,
                .viewTypeName = "Building",
                .viewName = "Side Road",
                .createdAt = "2020-09-01T08:00:00+0800",
                .viewObjectList = {
                    {
                        .objectTypeID = 5,
                        .name = "curb",
                        .meshCounts = { 1000, 1000, 1000, 65 },
                        .renderChannels = RenderChannel::Image
                    },
                    {
                        .objectTypeID = 6,
                        .name = "arterial",
                        .meshCounts = { 1000, 2000, 2700 },
                        .renderChannels = RenderChannel::Image
                    },
                    {
                        .objectTypeID = 7,
                        .name = "door",
                        .meshCounts = { 60, 40, 200 },
                        .renderChannels = RenderChannel::Buffer | RenderChannel::Printer
                    },
                    {
                        .objectTypeID = 8,
                        .name = "wall",
                        .meshCounts = { 200, 500, 302 },
                        .renderChannels = RenderChannel::Buffer | RenderChannel::Image | RenderChannel::Window | RenderChannel::Printer
                    },
                },
            },
            {
                .viewId = 3,
                .viewTypeName = "Building",
                .viewName = "Architecture",
                .createdAt = "2020-09-01T08:00:00+0800",
                .viewObjectList = {
                    {
                        .objectTypeID = 9,
                        .name = "skeleton",
                        .meshCounts = { 1000, 1000, 1000, 320 },
                        .renderChannels = RenderChannel::Buffer
                    },
                    {
                        .objectTypeID = 10,
                        .name = "roof",
                        .meshCounts = { 500, 501 },
                        .renderChannels = RenderChannel::Window
                    },
                    {
                        .objectTypeID = 11,
                        .name = "table",
                        .meshCounts = { 50, 50, 100, 100 },
                        .renderChannels = RenderChannel::Image
                    },
                    {
                        .objectTypeID = 12,
                        .name = "carpet",
                        .meshCounts = { 2, 2, 2, 1, 3 },
                        .renderChannels = RenderChannel::Printer
                    },
                },
            },
        },
        .highResolutionObjectSet = {
            "1-1",
            "2-1",
            "5-2",
            "6-2",
            "9-3",
            "10-3",
        },
        .meshCount = 50000,
    };
}