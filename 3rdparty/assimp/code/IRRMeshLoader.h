/*
Open Asset Import Library (ASSIMP)
----------------------------------------------------------------------

Copyright (c) 2006-2010, ASSIMP Development Team
All rights reserved.

Redistribution and use of this software in source and binary forms,
with or without modification, are permitted provided that the
following conditions are met:

* Redistributions of source code must retain the above
  copyright notice, this list of conditions and the
  following disclaimer.

* Redistributions in binary form must reproduce the above
  copyright notice, this list of conditions and the
  following disclaimer in the documentation and/or other
  materials provided with the distribution.

* Neither the name of the ASSIMP team, nor the names of its
  contributors may be used to endorse or promote products
  derived from this software without specific prior
  written permission of the ASSIMP Development Team.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------
*/

/** @file IRRMeshLoader.h
 *  @brief Declaration of the .irrMesh (Irrlight Engine Mesh Format)
 *  importer class.
 */
#ifndef AI_IRRMESHLOADER_H_INCLUDED
#define AI_IRRMESHLOADER_H_INCLUDED

#include "BaseImporter.h"
#include "IRRShared.h"

namespace Assimp    {

// ---------------------------------------------------------------------------
/** IrrMesh importer class.
 *
 * IrrMesh is the native file format of the Irrlight engine and its editor
 * irrEdit. As IrrEdit itself is capable of importing quite many file formats,
 * it might be a good file format for data exchange.
 */
class IRRMeshImporter : public BaseImporter, public IrrlichtBase
{
    friend class Importer;

protected:
    /** Constructor to be privately used by Importer */
    IRRMeshImporter();

    /** Destructor, private as well */
    ~IRRMeshImporter();

public:

    // -------------------------------------------------------------------
    /** Returns whether the class can handle the format of the given file.
     *  See BaseImporter::CanRead() for details.
     */
    bool CanRead( const std::string& pFile, IOSystem* pIOHandler,
        bool checkSig) const;

protected:

    // -------------------------------------------------------------------
    /** Called by Importer::GetExtensionList() for each loaded importer.
     * See BaseImporter::GetExtensionList() for details
     */
    void GetExtensionList(std::set<std::string>& extensions);

    // -------------------------------------------------------------------
    /** Imports the given file into the given scene structure.
     * See BaseImporter::InternReadFile() for details
     */
    void InternReadFile( const std::string& pFile, aiScene* pScene,
        IOSystem* pIOHandler);

};

} // end of namespace Assimp

#endif // AI_IRRMESHIMPORTER_H_INC
