#ifndef __BASE_LOADER_ZBOOT_OBJECT_HH__
#define __BASE_LOADER_ZBOOT_OBJECT_HH__

#include "base/loader/image_file_data.hh"
#include "base/loader/object_file.hh"

namespace gem5 {

namespace loader {

class ZBootObjectFormat : public ObjectFileFormat
{
public:
    ObjectFile *load(ImageFileDataPtr data) override;

};

class ZBootObject : public ObjectFile
{
public:
    ZBootObject(ImageFileDataPtr ifd);
    ~ZBootObject();

};

}

}

#endif // __BASE_LOADER_ZBOOT_OBJECT_HH__
