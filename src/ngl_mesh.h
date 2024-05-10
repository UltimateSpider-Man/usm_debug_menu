#pragma once

#include "hashstring.h"
#include "ngl_math.h"
#include "log.h"
#include "variable.h"

#include "mstring.h"


struct nglMeshSection;
struct nglMeshFile;

struct nglMeshParams {
    uint32_t Flags;
    int NBones;
    math::MatClass<4, 3> *field_8;
    int field_C;

    math::VecClass<3, 1> Scale;

    nglMeshParams() = default;

    nglMeshParams(uint32_t f) : Flags(f) {}
};

constexpr auto NGLMESH_PROCESSED = 0x10000;
constexpr auto NGLMESH_SCRATCH_MESH = 0x20000;

struct tlInstanceBankResourceDirectory {
    int m_vtbl;
};


        Var<tlInstanceBankResourceDirectory*> nglMeshDirectory = (0x00972810);


struct nglMesh {
    tlHashString Name;
    uint32_t Flags;
    uint32_t NSections;


    struct {
        int field_0;
        nglMeshSection *Section;
    } * Sections;
    int NBones;
    math::MatClass<4, 3> *Bones;
    int NLODs;
    struct Lod {
        nglMesh *field_0;
        int field_4;
    };

    Lod *LODs;
    math::VecClass<3, 1> field_20;
    float SphereRadius;
    nglMeshFile *File;
    nglMesh *NextMesh;
    int field_3C;

    nglMesh* nglGetMesh(const tlHashString& a1, bool a2)
    {
        nglMesh*(__fastcall * Find)(void*, int, const tlHashString*) = CAST(Find, get_vfunc(nglMeshDirectory()->m_vtbl, 0xC));
        auto* v4 = Find(nglMeshDirectory(), 0, &a1);
        if (v4 == nullptr && a2) {
            auto* v2 = a1.c_str();
        }

        return v4;
    }


    static tlHashString *get_string(nglMesh *Mesh);
};