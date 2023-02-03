#include "data.h"

ModelObjectsInfo getModelObjectsInfo() {
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
                    },
                    {
                        .objectTypeID = 2,
                        .name = "window",
                        .meshCounts = { 3000, 4000, 4000 },
                    },
                    {
                        .objectTypeID = 3,
                        .name = "pool",
                        .meshCounts = { 100, 101 },
                    },
                    {
                        .objectTypeID = 4,
                        .name = "pinball arcade",
                        .meshCounts = { 1000, 999 },
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
                    },
                    {
                        .objectTypeID = 6,
                        .name = "arterial",
                        .meshCounts = { 1000, 2000, 2700 },
                    },
                    {
                        .objectTypeID = 7,
                        .name = "door",
                        .meshCounts = { 60, 40, 200 },
                    },
                    {
                        .objectTypeID = 8,
                        .name = "wall",
                        .meshCounts = { 200, 500, 302 },
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
                    },
                    {
                        .objectTypeID = 10,
                        .name = "roof",
                        .meshCounts = { 500, 501 },
                    },
                    {
                        .objectTypeID = 11,
                        .name = "table",
                        .meshCounts = { 50, 50, 100, 100 },
                    },
                    {
                        .objectTypeID = 12,
                        .name = "carpet",
                        .meshCounts = { 2, 2, 2, 1, 3 },
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