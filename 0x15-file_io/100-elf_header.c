#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void close_elf(int elf_fd);

/**
 * main - Displays the information contained in the ELF header
 *        at the start of an ELF file.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: 0 on success.
 *
 * Description: If the file is not an ELF File or
 * the function fails - exit code 98.
 */
int main(int __attribute__((__unused__)) argc, char *argv[])
{
    int elf_fd, read_result;
    Elf64_Ehdr header;

    elf_fd = open(argv[1], O_RDONLY);
    if (elf_fd == -1)
    {
        dprintf(STDERR_FILENO, "Error: Can't read file %s\n", argv[1]);
        exit(98);
    }

    read_result = read(elf_fd, &header, sizeof(Elf64_Ehdr));
    if (read_result == -1)
    {
        close_elf(elf_fd);
        dprintf(STDERR_FILENO, "Error: `%s`: No such file\n", argv[1]);
        exit(98);
    }

    if (header.e_ident[0] != 127 || header.e_ident[1] != 'E' || header.e_ident[2] != 'L' || header.e_ident[3] != 'F')
    {
        close_elf(elf_fd);
        dprintf(STDERR_FILENO, "Error: Not an ELF file\n");
        exit(98);
    }

    printf("ELF Header:\n Magic:");
    for (int i = 0; i < EI_NIDENT; i++)
        printf(" %02x", header.e_ident[i]);
    printf("\n");

    printf(" Class: ");
    printf(header.e_ident[EI_CLASS] == ELFCLASS32 ? "ELF32\n" : "ELF64\n");

    printf(" Data: ");
    printf(header.e_ident[EI_DATA] == ELFDATA2LSB ? "2's complement, little endian\n" :
           header.e_ident[EI_DATA] == ELFDATA2MSB ? "2's complement, big endian\n" : "none\n");

    printf(" Version: %d%s\n", header.e_ident[EI_VERSION], header.e_ident[EI_VERSION] == EV_CURRENT ? " (current)" : "");

    printf(" OS/ABI: ");
    switch (header.e_ident[EI_OSABI])
    {
    case ELFOSABI_NONE:
        printf("UNIX - System V\n");
        break;
    case ELFOSABI_HPUX:
        printf("UNIX - HP-UX\n");
        break;
    case ELFOSABI_NETBSD:
        printf("UNIX - NetBSD\n");
        break;
    case ELFOSABI_LINUX:
        printf("UNIX - Linux\n");
        break;
    case ELFOSABI_SOLARIS:
        printf("UNIX - Solaris\n");
        break;
    case ELFOSABI_IRIX:
        printf("UNIX - IRIX\n");
        break;
    case ELFOSABI_FREEBSD:
        printf("UNIX - FreeBSD\n");
        break;
    case ELFOSABI_TRU64:
        printf("UNIX - TRU64\n");
        break;
    case ELFOSABI_ARM:
        printf("ARM\n");
        break;
    case ELFOSABI_STANDALONE:
        printf("Standalone App\n");
        break;
    default:
        printf("<unknown: %x>\n", header.e_ident[EI_OSABI]);
    }

    printf(" ABI Version: %d\n", header.e_ident[EI_ABIVERSION]);

    printf(" Type: ");
    int e_type = header.e_type;
    if (header.e_ident[EI_DATA] == ELFDATA2MSB)
        e_type >>= 8;
    switch (e_type)
    {
    case ET_NONE:
        printf("NONE (None)\n");
        break;
    case ET_REL:
        printf("REL (Relocatable file)\n");
        break;
    case ET_EXEC:
        printf("EXEC (Executable file)\n");
        break;
    case ET_DYN:
        printf("DYN (Shared object file)\n");
        break;
    case ET_CORE:
        printf("CORE (Core file)\n");
        break;
    default:
        printf("<unknown: %x>\n", e_type);
    }

    printf(" Entry point address: ");
    unsigned long int e_entry = header.e_entry;
    if (header.e_ident[EI_DATA] == ELFDATA2MSB)
    {
        e_entry = ((e_entry << 8) & 0xFF00FF00) | ((e_entry >> 8) & 0xFF00FF);
        e_entry = (e_entry << 16) | (e_entry >> 16);
    }
    printf(header.e_ident[EI_CLASS] == ELFCLASS32 ? "%#x\n" : "%#lx\n", header.e_ident[EI_CLASS] == ELFCLASS32 ? (unsigned int)e_entry : e_entry);

    close_elf(elf_fd);
    return (0);
}

/**
 * close_elf - Closes an ELF file.
 * @elf_fd: The file descriptor of the ELF file.
 *
 * Description: If the file cannot be closed - exit code 98.
 */
void close_elf(int elf_fd)
{
    if (close(elf_fd) == -1)
    {
        dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", elf_fd);
        exit(98);
    }
}
