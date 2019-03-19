//
// Created by Ion Agorria on 8/04/18
//
#ifndef OPENE2140_ASSETMANAGER_H
#define OPENE2140_ASSETMANAGER_H

#include <string>
#include <map>
#include <list>
#include "asset.h"
#include "core/errorpossible.h"
#include "math/vector2.h"
#include "io/log.h"

/**
 * Handles the loading of different assets
 */
class Game;
class AssetImage;
class AssetManager: public IErrorPossible {
private:
    /**
     * Log for object
     */
    log_ptr log;

    /**
     * Game which assets belong to
     */
    std::shared_ptr<Game> game;

    /**
     * Contains all assets in this manager
     */
    std::unordered_map<asset_path, std::shared_ptr<Asset>> assets;

    /**
     * Number of assets loaded
     */
    int assetsCount;

    /**
     * Adds asset to manager in specified path
     *
     * @param asset to add
     * @return true if added or false if asset exists on same path
     */
    bool addAsset(std::shared_ptr<Asset> asset);

    /**
     * Removes asset from manager in specified path
     *
     * @param asset to remove
     * @return true if removed
     */
    bool removeAsset(const asset_path& path);

    /**
     * Scans a container which contains assets to get the contents (folder or mapped file with paths)
     *
     * @param path of containers root
     * @param name of container
     * @return true if succeeded
     */
    bool scanContainer(const std::string& path, const std::string& name);

    /**
     * Scans assets from WD file container and stores in manager
     *
     * @param path to use as assets root
     * @param name of container
     * @return amount of loaded assets or -1 if error occurred
     */
    int scanContainerWD(const std::string& path, const std::string& name);

    /**
     * Scans assets from directory container and stores in manager
     *
     * @param path to use as assets root
     * @param name of container
     * @return amount of loaded assets or -1 if error occurred
     */
    int scanContainerDir(const std::string& path, const std::string& name);

    /**
     * Processes intermediate assets if they can be converted to different assets
     */
    void processIntermediates();

    /**
     * Processes the content of a MIX asset for more assets
     *
     * @param path containing MIX asset
     * @return amount of added assets or -1 if error
     */
    int processIntermediateMIX(const asset_path& path);

    /**
     * Processes the images
     */
    void processImages(unsigned int textureSize, unsigned int batchSize, std::vector<AssetImage*>& assetImages);

    /**
     * Each WD container file record struct
     */
    struct WDFileRecord {
        unsigned int fileOffset;
        unsigned int fileSize;
        unsigned int unused1;
        unsigned int unused2;
        unsigned int checkSum;
        unsigned int nameOffset;
    };

    /**
     * MIX file header struct
     */
    struct MIXHeader {
        unsigned int unused;
        unsigned int streamsCount;
        unsigned int streamsOffset;
        unsigned int palettesCount;
        unsigned int palettesFirstIndex;
        unsigned int palettesOffset;
    };

    /**
     * Image size struct with shorts
     */
    struct ImageSize16 {
        unsigned short width;
        unsigned short height;
    };

    /**
     * Segmented image header
     */
    struct SegmentedImageHeader {
        unsigned int width;
        unsigned int height;
        unsigned int dataBlockSize;
        unsigned int scanLinesCount;
        unsigned int segmentBlockSize;
        unsigned int unknown6;
        unsigned int unknown7;
        unsigned int unknown8;
        unsigned int unknown9;
    };

    /**
     * Segmented image segment
     */
    struct SegmentedImageSegment {
        byte padding;
        byte width;
    };

public:
    /**
     * Constructs loader
     */
    AssetManager(std::shared_ptr<Game> game);

    /**
     * Destructs loader and cleans any loaded assets
     */
    ~AssetManager();

    /**
     * Disable copy/move
     */
    NON_COPYABLE_NOR_MOVABLE(AssetManager)

    /**
     * Gets the loaded asset
     *
     * @return asset
     */
    std::shared_ptr<Asset> getAsset(const asset_path& path);

    /**
     * Gets the loaded asset with specified cast
     *
     * @return asset
     */
    template <typename T>
    std::shared_ptr<T> getAsset(const asset_path& path);

    /**
     * @return the count of assets loaded
     */
    int getAssetsCount();

    /**
     * Clears all loaded assets from manager
     */
    void clearAssets();

    /**
     * Loads the assets data from files into memory
     */
    void loadAssets();

    /**
     * (Re)Loads the volatile assets data using memory data
     */
    void refreshAssets();
};

#endif //OPENE2140_ASSETMANAGER_H