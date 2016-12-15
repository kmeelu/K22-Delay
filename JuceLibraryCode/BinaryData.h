/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#ifndef BINARYDATA_H_49475573_INCLUDED
#define BINARYDATA_H_49475573_INCLUDED

namespace BinaryData
{
    extern const char*   Background_cpp;
    const int            Background_cppSize = 3144041;

    extern const char*   Images_cpp;
    const int            Images_cppSize = 2233171;

    extern const char*   Images_h;
    const int            Images_hSize = 2248;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Number of elements in the namedResourceList array.
    const int namedResourceListSize = 3;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();
}

#endif
