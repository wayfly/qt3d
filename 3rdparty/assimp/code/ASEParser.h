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


/** @file Defines the helper data structures for importing ASE files  */
#ifndef AI_ASEFILEHELPER_H_INC
#define AI_ASEFILEHELPER_H_INC

// STL/CRT headers
#include <string>
#include <vector>
#include <list>

// public ASSIMP headers
#include "../include/aiTypes.h"
#include "../include/aiMesh.h"
#include "../include/aiAnim.h"

// for some helper routines like IsSpace()
#include "ParsingUtils.h"
#include "qnan.h"

// ASE is quite similar to 3ds. We can reuse some structures
#include "3DSLoader.h"

namespace Assimp    {
namespace ASE    {

using namespace D3DS;

// ---------------------------------------------------------------------------
/** Helper structure representing an ASE material */
struct Material : public D3DS::Material
{
    //! Default constructor
    Material() : pcInstance(NULL), bNeed (false)
    {}

    //! Contains all sub materials of this material
    std::vector<Material> avSubMaterials;

    //! MaterialHelper object
    MaterialHelper* pcInstance;

    //! Can we remove this material?
    bool bNeed;
};

// ---------------------------------------------------------------------------
/** Helper structure to represent an ASE file face */
struct Face : public FaceWithSmoothingGroup
{
    //! Default constructor. Initializes everything with 0
    Face()
    {
        mColorIndices[0] = mColorIndices[1] = mColorIndices[2] = 0;
        for (unsigned int i = 0; i < AI_MAX_NUMBER_OF_TEXTURECOORDS;++i)
        {
            amUVIndices[i][0] = amUVIndices[i][1] = amUVIndices[i][2] = 0;
        }

        iMaterial = DEFAULT_MATINDEX;
        iFace = 0;
    }

    //! special value to indicate that no material index has
    //! been assigned to a face. The default material index
    //! will replace this value later.
    static const unsigned int DEFAULT_MATINDEX = 0xFFFFFFFF;



    //! Indices into each list of texture coordinates
    unsigned int amUVIndices[AI_MAX_NUMBER_OF_TEXTURECOORDS][3];

    //! Index into the list of vertex colors
    unsigned int mColorIndices[3];

    //! (Sub)Material index to be assigned to this face
    unsigned int iMaterial;

    //! Index of the face. It is not specified whether it is
    //! a requirement of the file format that all faces are
    //! written in sequential order, so we have to expect this case
    unsigned int iFace;
};

// ---------------------------------------------------------------------------
/** Helper structure to represent an ASE file bone */
struct Bone
{
    //! Constructor
    Bone()
    {
        static int iCnt = 0;

        // Generate a default name for the bone
        char szTemp[128];
        ::sprintf(szTemp,"UNNAMED_%i",iCnt++);
        mName = szTemp;
    }

    //! Construction from an existing name
    Bone( const std::string& name)
        :    mName    (name)
    {}

    //! Name of the bone
    std::string mName;
};

// ---------------------------------------------------------------------------
/** Helper structure to represent an ASE file bone vertex */
struct BoneVertex
{
    //! Bone and corresponding vertex weight.
    //! -1 for unrequired bones ....
    std::vector<std::pair<int,float> > mBoneWeights;

    //! Position of the bone vertex.
    //! MUST be identical to the vertex position
    //aiVector3D mPosition;
};

// ---------------------------------------------------------------------------
/** Helper structure to represent an ASE file animation */
struct Animation
{
    enum Type
    {
        TRACK   = 0x0,
        BEZIER  = 0x1,
        TCB        = 0x2
    } mRotationType, mScalingType, mPositionType;

    Animation()
        :    mRotationType    (TRACK)
        ,    mScalingType    (TRACK)
        ,    mPositionType    (TRACK)
    {}

    //! List of track rotation keyframes
    std::vector< aiQuatKey > akeyRotations;

    //! List of track position keyframes
    std::vector< aiVectorKey > akeyPositions;

    //! List of track scaling keyframes
    std::vector< aiVectorKey > akeyScaling;

};

// ---------------------------------------------------------------------------
/** Helper structure to represent the inheritance information of an ASE node */
struct InheritanceInfo
{
    //! Default constructor
    InheritanceInfo()
    {
        // set the inheritance flag for all axes by default to true
        for (unsigned int i = 0; i < 3;++i)
            abInheritPosition[i] = abInheritRotation[i] = abInheritScaling[i] = true;
    }

    //! Inherit the parent's position?, axis order is x,y,z
    bool abInheritPosition[3];

    //! Inherit the parent's rotation?, axis order is x,y,z
    bool abInheritRotation[3];

    //! Inherit the parent's scaling?, axis order is x,y,z
    bool abInheritScaling[3];
};

// ---------------------------------------------------------------------------
/** Represents an ASE file node. Base class for mesh, light and cameras */
struct BaseNode
{
    enum Type {Light, Camera, Mesh, Dummy} mType;

    //! Constructor. Creates a default name for the node
    BaseNode(Type _mType)
        : mType            (_mType)
        , mProcessed    (false)
    {
        // generate a default name for the  node
        static int iCnt = 0;
        char szTemp[128]; // should be sufficiently large
        ::sprintf(szTemp,"UNNAMED_%i",iCnt++);
        mName = szTemp;

        // Set mTargetPosition to qnan
        const float qnan = get_qnan();
        mTargetPosition.x = qnan;
    }

    //! Name of the mesh
    std::string mName;

    //! Name of the parent of the node
    //! "" if there is no parent ...
    std::string mParent;

    //! Transformation matrix of the node
    aiMatrix4x4 mTransform;

    //! Target position (target lights and cameras)
    aiVector3D mTargetPosition;

    //! Specifies which axes transformations a node inherits
    //! from its parent ...
    InheritanceInfo inherit;

    //! Animation channels for the node
    Animation mAnim;

    //! Needed for lights and cameras: target animation channel
    //! Should contain position keys only.
    Animation mTargetAnim;

    bool mProcessed;
};

// ---------------------------------------------------------------------------
/** Helper structure to represent an ASE file mesh */
struct Mesh : public MeshWithSmoothingGroups<ASE::Face>, public BaseNode
{
    //! Constructor.
    Mesh()
        : BaseNode    (BaseNode::Mesh)
        , bSkip        (false)
    {
        // use 2 texture vertex components by default
        for (unsigned int c = 0; c < AI_MAX_NUMBER_OF_TEXTURECOORDS;++c)
            this->mNumUVComponents[c] = 2;

        // setup the default material index by default
        iMaterialIndex = Face::DEFAULT_MATINDEX;
    }

    //! List of all texture coordinate sets
    std::vector<aiVector3D> amTexCoords[AI_MAX_NUMBER_OF_TEXTURECOORDS];

    //! List of all vertex color sets.
    std::vector<aiColor4D> mVertexColors;

    //! List of all bone vertices
    std::vector<BoneVertex> mBoneVertices;

    //! List of all bones
    std::vector<Bone> mBones;

    //! Material index of the mesh
    unsigned int iMaterialIndex;

    //! Number of vertex components for each UVW set
    unsigned int mNumUVComponents[AI_MAX_NUMBER_OF_TEXTURECOORDS];

    //! used internally
    bool bSkip;
};

// ---------------------------------------------------------------------------
/** Helper structure to represent an ASE light source */
struct Light : public BaseNode
{
    enum LightType
    {
        OMNI,
        TARGET,
        FREE,
        DIRECTIONAL
    };

    //! Constructor.
    Light()
        : BaseNode     (BaseNode::Light)
        , mLightType (OMNI)
        , mColor     (1.f,1.f,1.f)
        , mIntensity (1.f) // light is white by default
        , mAngle     (45.f)
        , mFalloff     (0.f)
    {
    }

    LightType mLightType;
    aiColor3D mColor;
    float mIntensity;
    float mAngle; // in degrees
    float mFalloff;
};

// ---------------------------------------------------------------------------
/** Helper structure to represent an ASE camera */
struct Camera : public BaseNode
{
    enum CameraType
    {
        FREE,
        TARGET
    };

    //! Constructor
    Camera()
        : BaseNode      (BaseNode::Camera)
        , mFOV        (0.75f)   // in radians
        , mNear       (0.1f)
        , mFar        (1000.f)  // could be zero
        , mCameraType (FREE)
    {
    }

    float mFOV, mNear, mFar;
    CameraType mCameraType;
};

// ---------------------------------------------------------------------------
/** Helper structure to represent an ASE helper object (dummy) */
struct Dummy : public BaseNode
{
    //! Constructor
    Dummy()
        : BaseNode    (BaseNode::Dummy)
    {
    }
};

// Parameters to Parser::Parse()
#define AI_ASE_NEW_FILE_FORMAT 200
#define AI_ASE_OLD_FILE_FORMAT 110

// Internally we're a little bit more tolerant
#define AI_ASE_IS_NEW_FILE_FORMAT()    (iFileFormat >= 200)
#define AI_ASE_IS_OLD_FILE_FORMAT()    (iFileFormat < 200)

// -------------------------------------------------------------------------------
/** \brief Class to parse ASE files
 */
class Parser
{

private:

    Parser() {}

public:

    // -------------------------------------------------------------------
    //! Construct a parser from a given input file which is
    //! guaranted to be terminated with zero.
    //! @param szFile Input file
    //! @param fileFormatDefault Assumed file format version. If the
    //!   file format is specified in the file the new value replaces
    //!   the default value.
    Parser (const char* szFile, unsigned int fileFormatDefault);

    // -------------------------------------------------------------------
    //! Parses the file into the parsers internal representation
    void Parse();


private:

    // -------------------------------------------------------------------
    //! Parse the *SCENE block in a file
    void ParseLV1SceneBlock();

    // -------------------------------------------------------------------
    //! Parse the *MESH_SOFTSKINVERTS block in a file
    void ParseLV1SoftSkinBlock();

    // -------------------------------------------------------------------
    //! Parse the *MATERIAL_LIST block in a file
    void ParseLV1MaterialListBlock();

    // -------------------------------------------------------------------
    //! Parse a *<xxx>OBJECT block in a file
    //! \param mesh Node to be filled
    void ParseLV1ObjectBlock(BaseNode& mesh);

    // -------------------------------------------------------------------
    //! Parse a *MATERIAL blocks in a material list
    //! \param mat Material structure to be filled
    void ParseLV2MaterialBlock(Material& mat);

    // -------------------------------------------------------------------
    //! Parse a *NODE_TM block in a file
    //! \param mesh Node (!) object to be filled
    void ParseLV2NodeTransformBlock(BaseNode& mesh);

    // -------------------------------------------------------------------
    //! Parse a *TM_ANIMATION block in a file
    //! \param mesh Mesh object to be filled
    void ParseLV2AnimationBlock(BaseNode& mesh);
    void ParseLV3PosAnimationBlock(ASE::Animation& anim);
    void ParseLV3ScaleAnimationBlock(ASE::Animation& anim);
    void ParseLV3RotAnimationBlock(ASE::Animation& anim);

    // -------------------------------------------------------------------
    //! Parse a *MESH block in a file
    //! \param mesh Mesh object to be filled
    void ParseLV2MeshBlock(Mesh& mesh);

    // -------------------------------------------------------------------
    //! Parse a *LIGHT_SETTINGS block in a file
    //! \param light Light object to be filled
    void ParseLV2LightSettingsBlock(Light& light);

    // -------------------------------------------------------------------
    //! Parse a *CAMERA_SETTINGS block in a file
    //! \param cam Camera object to be filled
    void ParseLV2CameraSettingsBlock(Camera& cam);

    // -------------------------------------------------------------------
    //! Parse the *MAP_XXXXXX blocks in a material
    //! \param map Texture structure to be filled
    void ParseLV3MapBlock(Texture& map);

    // -------------------------------------------------------------------
    //! Parse a *MESH_VERTEX_LIST block in a file
    //! \param iNumVertices Value of *MESH_NUMVERTEX, if present.
    //! Otherwise zero. This is used to check the consistency of the file.
    //! A warning is sent to the logger if the validations fails.
    //! \param mesh Mesh object to be filled
    void ParseLV3MeshVertexListBlock(
        unsigned int iNumVertices,Mesh& mesh);

    // -------------------------------------------------------------------
    //! Parse a *MESH_FACE_LIST block in a file
    //! \param iNumFaces Value of *MESH_NUMFACES, if present.
    //! Otherwise zero. This is used to check the consistency of the file.
    //! A warning is sent to the logger if the validations fails.
    //! \param mesh Mesh object to be filled
    void ParseLV3MeshFaceListBlock(
        unsigned int iNumFaces,Mesh& mesh);

    // -------------------------------------------------------------------
    //! Parse a *MESH_TVERT_LIST block in a file
    //! \param iNumVertices Value of *MESH_NUMTVERTEX, if present.
    //! Otherwise zero. This is used to check the consistency of the file.
    //! A warning is sent to the logger if the validations fails.
    //! \param mesh Mesh object to be filled
    //! \param iChannel Output UVW channel
    void ParseLV3MeshTListBlock(
        unsigned int iNumVertices,Mesh& mesh, unsigned int iChannel = 0);

    // -------------------------------------------------------------------
    //! Parse a *MESH_TFACELIST block in a file
    //! \param iNumFaces Value of *MESH_NUMTVFACES, if present.
    //! Otherwise zero. This is used to check the consistency of the file.
    //! A warning is sent to the logger if the validations fails.
    //! \param mesh Mesh object to be filled
    //! \param iChannel Output UVW channel
    void ParseLV3MeshTFaceListBlock(
        unsigned int iNumFaces,Mesh& mesh, unsigned int iChannel = 0);

    // -------------------------------------------------------------------
    //! Parse an additional mapping channel
    //! (specified via *MESH_MAPPINGCHANNEL)
    //! \param iChannel Channel index to be filled
    //! \param mesh Mesh object to be filled
    void ParseLV3MappingChannel(
        unsigned int iChannel, Mesh& mesh);

    // -------------------------------------------------------------------
    //! Parse a *MESH_CVERTLIST block in a file
    //! \param iNumVertices Value of *MESH_NUMCVERTEX, if present.
    //! Otherwise zero. This is used to check the consistency of the file.
    //! A warning is sent to the logger if the validations fails.
    //! \param mesh Mesh object to be filled
    void ParseLV3MeshCListBlock(
        unsigned int iNumVertices, Mesh& mesh);

    // -------------------------------------------------------------------
    //! Parse a *MESH_CFACELIST block in a file
    //! \param iNumFaces Value of *MESH_NUMCVFACES, if present.
    //! Otherwise zero. This is used to check the consistency of the file.
    //! A warning is sent to the logger if the validations fails.
    //! \param mesh Mesh object to be filled
    void ParseLV3MeshCFaceListBlock(
        unsigned int iNumFaces, Mesh& mesh);

    // -------------------------------------------------------------------
    //! Parse a *MESH_NORMALS block in a file
    //! \param mesh Mesh object to be filled
    void ParseLV3MeshNormalListBlock(Mesh& mesh);

    // -------------------------------------------------------------------
    //! Parse a *MESH_WEIGHTSblock in a file
    //! \param mesh Mesh object to be filled
    void ParseLV3MeshWeightsBlock(Mesh& mesh);

    // -------------------------------------------------------------------
    //! Parse the bone list of a file
    //! \param mesh Mesh object to be filled
    //! \param iNumBones Number of bones in the mesh
    void ParseLV4MeshBones(unsigned int iNumBones,Mesh& mesh);

    // -------------------------------------------------------------------
    //! Parse the bone vertices list of a file
    //! \param mesh Mesh object to be filled
    //! \param iNumVertices Number of vertices to be parsed
    void ParseLV4MeshBonesVertices(unsigned int iNumVertices,Mesh& mesh);

    // -------------------------------------------------------------------
    //! Parse a *MESH_FACE block in a file
    //! \param out receive the face data
    void ParseLV4MeshFace(ASE::Face& out);

    // -------------------------------------------------------------------
    //! Parse a *MESH_VERT block in a file
    //! (also works for MESH_TVERT, MESH_CFACE, MESH_VERTCOL  ...)
    //! \param apOut Output buffer (3 floats)
    //! \param rIndexOut Output index
    void ParseLV4MeshFloatTriple(float* apOut, unsigned int& rIndexOut);

    // -------------------------------------------------------------------
    //! Parse a *MESH_VERT block in a file
    //! (also works for MESH_TVERT, MESH_CFACE, MESH_VERTCOL  ...)
    //! \param apOut Output buffer (3 floats)
    void ParseLV4MeshFloatTriple(float* apOut);

    // -------------------------------------------------------------------
    //! Parse a *MESH_TFACE block in a file
    //! (also works for MESH_CFACE)
    //! \param apOut Output buffer (3 ints)
    //! \param rIndexOut Output index
    void ParseLV4MeshLongTriple(unsigned int* apOut, unsigned int& rIndexOut);

    // -------------------------------------------------------------------
    //! Parse a *MESH_TFACE block in a file
    //! (also works for MESH_CFACE)
    //! \param apOut Output buffer (3 ints)
    void ParseLV4MeshLongTriple(unsigned int* apOut);

    // -------------------------------------------------------------------
    //! Parse a single float element
    //! \param fOut Output float
    void ParseLV4MeshFloat(float& fOut);

    // -------------------------------------------------------------------
    //! Parse a single int element
    //! \param iOut Output integer
    void ParseLV4MeshLong(unsigned int& iOut);

    // -------------------------------------------------------------------
    //! Skip everything to the next: '*' or '\0'
    bool SkipToNextToken();

    // -------------------------------------------------------------------
    //! Skip the current section until the token after the closing }.
    //! This function handles embedded subsections correctly
    bool SkipSection();

    // -------------------------------------------------------------------
    //! Output a warning to the logger
    //! \param szWarn Warn message
    void LogWarning(const char* szWarn);

    // -------------------------------------------------------------------
    //! Output a message to the logger
    //! \param szWarn Message
    void LogInfo(const char* szWarn);

    // -------------------------------------------------------------------
    //! Output an error to the logger
    //! \param szWarn Error message
    void LogError(const char* szWarn);

    // -------------------------------------------------------------------
    //! Parse a string, enclosed in double quotation marks
    //! \param out Output string
    //! \param szName Name of the enclosing element -> used in error
    //! messages.
    //! \return false if an error occured
    bool ParseString(std::string& out,const char* szName);

public:

    //! Pointer to current data
    const char* filePtr;

    //! background color to be passed to the viewer
    //! QNAN if none was found
    aiColor3D m_clrBackground;

    //! Base ambient color to be passed to all materials
    //! QNAN if none was found
    aiColor3D m_clrAmbient;

    //! List of all materials found in the file
    std::vector<Material> m_vMaterials;

    //! List of all meshes found in the file
    std::vector<Mesh> m_vMeshes;

    //! List of all dummies found in the file
    std::vector<Dummy> m_vDummies;

    //! List of all lights found in the file
    std::vector<Light> m_vLights;

    //! List of all cameras found in the file
    std::vector<Camera> m_vCameras;

    //! Current line in the file
    unsigned int iLineNumber;

    //! First frame
    unsigned int iFirstFrame;

    //! Last frame
    unsigned int iLastFrame;

    //! Frame speed - frames per second
    unsigned int iFrameSpeed;

    //! Ticks per frame
    unsigned int iTicksPerFrame;

    //! true if the last character read was an end-line character
    bool bLastWasEndLine;

    //! File format version
    unsigned int iFileFormat;
};


} // Namespace ASE
} // Namespace ASSIMP

#endif // !! include guard
