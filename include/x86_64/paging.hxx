#ifndef X86_64_PAGING_HXX
#define X86_64_PAGING_HXX

#include "std_extention.hxx"

namespace krn
{
    struct tbl_entry_t
    {
      public:
        bool present_ : 1 = false;
        bool rw_ : 1 = false;
        bool user_ : 1 = false; // user / supervisor
        bool pwt_ : 1 = false;  // write through
        bool pcd_ : 1 = false;  // cache disabled
        bool accessed_ : 1 = false;

      protected:
        u8 avl0_ : 1 = 0;

      public:
        u8 ps_ : 1 = 0; // optionally be

      protected:
        u8 avl2_ : 4 = 0;

      public:
        u64 paddr_ : 40 = 0;

      protected:
        u64 avl3_ : 11 = 0;

      public:
        bool xd_ : 1 = false; // execute disabled
    } __attribute__((packed));

    struct pml5_t
    {
        tbl_entry_t entries_[512];
    };

    struct pml4_t
    {
        tbl_entry_t entries_[512];
    };

    struct page_dir_ptr_tbl_t
    {
        // 1 G large page
        struct page_entry_t
        {
          public:
            bool present_ : 1 = false;
            bool rw_ : 1 = false;
            bool user_ : 1 = false; // user / supervisor
            bool pwt_ : 1 = false;  // write through
            bool pcd_ : 1 = false;  // cache disabled
            bool accessed_ : 1 = false;
            bool dirty_ : 1 = false;

          public:
            bool ps_ : 1 = true; // page size, this refer to a 2 M large page

          protected:
            bool global_ : 1 = false;
            u8 avl0_ : 3 = 0;

          public:
            bool pat_ : 1 = false; // page attribute

          protected:
            u32 rsvd0_ : 17 = 0;

          public:
            u64 paddr_ : 22 = 0;

          protected:
            u64 avl1_ : 7 = 0;

          public:
            u8 pk_ : 4 = 0;       // protection key
            bool xd_ : 1 = false; // execute disabled
        } __attribute__((packed));

        union entry_t
        {
            tbl_entry_t tbl_;
            page_entry_t page_;
        } __attribute__((packed));

        entry_t entries_[512];
    };

    struct page_dir_t
    {
        // 2 M large page
        struct page_entry_t
        {
          public:
            bool present_ : 1 = false;
            bool rw_ : 1 = false;
            bool user_ : 1 = false; // user / supervisor
            bool pwt_ : 1 = false;  // write through
            bool pcd_ : 1 = false;  // cache disabled
            bool accessed_ : 1 = false;
            bool dirty_ : 1 = false;

          public:
            bool ps_ : 1 = true; // page size, this refer to a 2 M large page

          protected:
            bool global_ : 1 = false;
            u8 avl0_ : 3 = 0;

          public:
            bool pat_ : 1 = false; // page attribute

          protected:
            u32 rsvd0_ : 8 = 0;

          public:
            u64 paddr_ : 31 = 0;

          protected:
            u64 avl1_ : 7 = 0;

          public:
            u8 pk_ : 4 = 0;       // protection key
            bool xd_ : 1 = false; // execute disabled
        } __attribute__((packed));

        union entry_t
        {
            tbl_entry_t tbl_;
            page_entry_t page_;
        } __attribute__((packed));

        entry_t entries_[512];
    };

    struct page_table_t
    {
        // 1 K page
        struct entry_t
        {
          public:
            bool present_ : 1 = false;
            bool rw_ : 1 = false;
            bool user_ : 1 = false; // user / supervisor
            bool pwt_ : 1 = false;  // write through
            bool pcd_ : 1 = false;  // cache disabled
            bool accessed_ : 1 = false;
            bool dirty_ : 1 = false;
            bool pat_ : 1 = false; // page attribute

          protected:
            bool global_ : 1 = false;
            u8 avl0_ : 3 = 0;

          public:
            u64 paddr_ : 40 = 0;

          protected:
            u64 avl1_ : 7 = 0;

          public:
            u8 pk_ : 4 = 0;       // protection key
            bool xd_ : 1 = false; // execute disabled
        } __attribute__((packed));

        entry_t entries_[512];
    };

    using paddr_t = u64;
    struct vaddr_t
    {
      public:
        u64 off_ : 12 = 0;   // offset
        u64 pte_ : 9 = 0;    // page table entry
        u64 pde_ : 9 = 0;    // page directory entry
        u64 pdptre_ : 9 = 0; // page directory pointer entry
        u64 pml4e_ : 9 = 0;
        u64 pml5e_ : 9 = 0;

      protected:
        u64 rsvd_ : 7 = 0; // canonical bits

      public:
        vaddr_t() = default;

        inline constexpr vaddr_t(u64 addr) { (*(castr(u64*, this))) = addr; }

        inline constexpr //
        operator u64() const
        {
            return *castr(const u64*, this);
        }

        inline constexpr vaddr_t& //
        operator=(u64 addr)
        {
            (*(castr(u64*, this))) = addr;
            return *this;
        }

        inline constexpr bool //
        operator<=(vaddr_t& addr) const
        {
            return casts(u64, *this) <= addr;
        }

        inline constexpr bool //
        operator>=(vaddr_t addr) const
        {
            return casts(u64, *this) >= addr;
        }

        inline constexpr bool //
        operator<(vaddr_t addr) const
        {
            return casts(u64, *this) < addr;
        }

        inline constexpr bool //
        operator>(vaddr_t addr) const
        {
            return casts(u64, *this) > addr;
        }

        inline constexpr void //
        set_canonical_bits()
        {
            if (pml5e_ & 0b100000000)
            {
                rsvd_ = 0b1111111;
            }
            else
            {
                rsvd_ = 0b0000000;
            }
        }
    } __attribute__((packed));

    static_assert(sizeof(vaddr_t) == sizeof(void*));
    static_assert(sizeof(page_table_t::entry_t) == sizeof(void*));
    static_assert(sizeof(page_dir_t::entry_t) == sizeof(void*));
    static_assert(sizeof(page_dir_ptr_tbl_t::entry_t) == sizeof(void*));
    static_assert(sizeof(tbl_entry_t) == sizeof(void*));

    // kernel virtual memory manager
    struct vmm
    {
        void //
        init();
    };

    // physical memory manager
    struct phy_mem_mgr
    {
        void //
        init();
    };

}; // namespace krn

#endif // X86_64_PAGING_HXX
