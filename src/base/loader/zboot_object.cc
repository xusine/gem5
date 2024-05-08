#include "base/loader/object_file.hh"
#include "zboot_object.hh"

namespace gem5 {


namespace loader {



ObjectFile *ZBootObjectFormat::load(ImageFileDataPtr data)
{
    // We will reference the QEMU implementation.
    // The reference QEMU implementation is in the following files:
    // - hw/arm/virt.c, line 2327
    // - hw/arm/boot.c, line 919
    // - hw/core/loader.c, line 901
    return nullptr;
}

}


}
