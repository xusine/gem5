#include "base/loader/object_file.hh"
#include "zboot_object.hh"

/* The PE/COFF MS-DOS stub magic number */
const uint8_t EFI_PE_MSDOS_MAGIC[] = "MZ";

/*
 * The Linux header magic number for a EFI PE/COFF
 * image targeting an unspecified architecture.
 */
const uint8_t EFI_PE_LINUX_MAGIC[] = "\xcd\x23\x82\x81";

/*
 * Bootable Linux kernel images may be packaged as EFI zboot images, which are
 * self-decompressing executables when loaded via EFI. The compressed payload
 * can also be extracted from the image and decompressed by a non-EFI loader.
 *
 * The de facto specification for this format is at the following URL:
 *
 * https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/drivers/firmware/efi/libstub/zboot-header.S
 *
 * This definition is based on Linux upstream commit 29636a5ce87beba.
 */
struct linux_efi_zboot_header {
    uint8_t     msdos_magic[2];         /* PE/COFF 'MZ' magic number */
    uint8_t     reserved0[2];
    uint8_t     zimg[4];                /* "zimg" for Linux EFI zboot images */
    uint32_t    payload_offset;         /* LE offset to compressed payload */
    uint32_t    payload_size;           /* LE size of the compressed payload */
    uint8_t     reserved1[8];
    char        compression_type[32];   /* Compression type, NUL terminated */
    uint8_t     linux_magic[4];         /* Linux header magic */
    uint32_t    pe_header_offset;       /* LE offset to the PE header */
};

namespace gem5 {


namespace loader {



ObjectFile *ZBootObjectFormat::load(ImageFileDataPtr data)
{
    // We will reference the QEMU implementation.
    // The reference QEMU implementation is in the following files:
    // - hw/arm/virt.c, line 2327
    // - hw/arm/boot.c, line 919
    // - hw/core/loader.c, line 901

    // At least the header should be there.
    if (data->len() < sizeof(linux_efi_zboot_header)) {
        return nullptr;
    }

    const linux_efi_zboot_header *header = reinterpret_cast<const linux_efi_zboot_header *>(data->data());

    // Check for the PE/COFF MS-DOS stub magic number.
    if (memcmp(header->msdos_magic, EFI_PE_MSDOS_MAGIC, sizeof(header->msdos_magic))) {
        return nullptr;
    }

    // Check zimg magic number.
    if (memcmp(header->zimg, "zimg", sizeof(header->zimg))) {
        return nullptr;
    }

    // Check for the Linux header magic number.
    if (memcmp(header->linux_magic, EFI_PE_LINUX_MAGIC, sizeof(header->linux_magic))) {
        return nullptr;
    }



    return nullptr;
}

}


}
