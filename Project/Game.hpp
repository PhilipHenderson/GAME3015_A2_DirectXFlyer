#include "World.hpp"
#include "InputHandler.hpp"
#include "CommandQueue.hpp"

// The Game class, inheriting from D3DApp, represents the core of the game application.
class Game : public D3DApp
{
public:
    // Constructor: Sets up the game with a given instance handle.
    Game(HINSTANCE hInstance);

    // Deleted copy constructor and assignment operator to prevent copying.
    Game(const Game& rhs) = delete;
    Game& operator=(const Game& rhs) = delete;

    // Destructor: Cleans up resources.
    ~Game();

    // Initializes the game components and resources.
    virtual bool Initialize() override;

private:
    // Handles window resizing events.
    virtual void OnResize() override;

    // Updates the game state every frame.
    virtual void Update(const GameTimer& gt) override;

    // Renders the game every frame.
    virtual void Draw(const GameTimer& gt) override;

    // Processes keyboard input each frame.
    void OnKeyboardInput(const GameTimer& gt);

    // Updates the camera's position and orientation.
    void UpdateCamera(const GameTimer& gt);

    // Animates materials if necessary, per frame.
    void AnimateMaterials(const GameTimer& gt);

    // Updates constant buffers for objects every frame.
    void UpdateObjectCBs(const GameTimer& gt);

    // Updates constant buffers for materials every frame.
    void UpdateMaterialCBs(const GameTimer& gt);

    // Updates the main pass constant buffer every frame.
    void UpdateMainPassCB(const GameTimer& gt);

    // Loads textures from files.
    void LoadTextures();

    // Creates the root signature for the GPU pipeline.
    void BuildRootSignature();

    // Creates descriptor heaps for resources.
    void BuildDescriptorHeaps();

    // Compiles shaders and defines the input layout.
    void BuildShadersAndInputLayout();

    // Prepares geometry for shapes to be rendered.
    void BuildShapeGeometry();

    // Creates the pipeline state objects (PSOs).
    void BuildPSOs();

    // Allocates frame resources.
    void BuildFrameResources();

    // Initializes materials used in the game.
    void BuildMaterials();

    // Organizes render items.
    void BuildRenderItems();

    // Draws render items with a given command list and list of items.
    void DrawRenderItems(ID3D12GraphicsCommandList* cmdList, const std::vector<RenderItem*>& ritems);

    // Utility functions for terrain.
    float GetHillsHeight(float x, float z) const;
    XMFLOAT3 GetHillsNormal(float x, float z) const;

    // Retrieves a set of static samplers for use in shaders.
    std::array<const CD3DX12_STATIC_SAMPLER_DESC, 6> GetStaticSamplers();

private:
    // Frame resources for triple buffering.
    std::vector<std::unique_ptr<FrameResource>> mFrameResources;
    FrameResource* mCurrFrameResource = nullptr;
    int mCurrFrameResourceIndex = 0;

    // Size of CBV/SRV descriptor.
    UINT mCbvSrvDescriptorSize = 0;

    // Root signature for the rendering pipeline.
    ComPtr<ID3D12RootSignature> mRootSignature = nullptr;

    // Descriptor heap for shader resource views.
    ComPtr<ID3D12DescriptorHeap> mSrvDescriptorHeap = nullptr;

    // Storage for geometry data.
    std::unordered_map<std::string, std::unique_ptr<MeshGeometry>> mGeometries;

    // Storage for material data.
    std::unordered_map<std::string, std::unique_ptr<Material>> mMaterials;

    // Storage for texture data.
    std::unordered_map<std::string, std::unique_ptr<Texture>> mTextures;

    // Compiled shader objects.
    std::unordered_map<std::string, ComPtr<ID3DBlob>> mShaders;

    // Input layout description for the vertex shader.
    std::vector<D3D12_INPUT_ELEMENT_DESC> mInputLayout;

    // Pipeline state object for opaque rendering.
    ComPtr<ID3D12PipelineState> mOpaquePSO = nullptr;

    // All renderable items in the scene.
    std::vector<std::unique_ptr<RenderItem>> mAllRitems;

    // Render items sorted by PSO (e.g., opaque, transparent).
    std::vector<RenderItem*> mOpaqueRitems;

    // Pass constant buffer for the main render pass.
    PassConstants mMainPassCB;

    // Camera position and orientation.
    XMFLOAT3 mEyePos = { 0.0f, 0.0f, -5.0f };
    XMFLOAT4X4 mView = MathHelper::Identity4x4();
    XMFLOAT4X4 mProj = MathHelper::Identity4x4();

    // Camera control variables.
    float mTheta = 1.3f * XM_PI;
    float mPhi = 0.4f * XM_PI;
    float mRadius = 2.5f;

    // Last mouse position for camera control.
    POINT mLastMousePos;

    // Camera object for view/projection calculations.
    Camera mCamera;

    // World object for managing game world entities and state.
    World mWorld;

    std::unique_ptr<InputHandler> mInputHandler;


    CommandQueue mCommandQueue;

public:
    // Accessors for game resources.
    std::vector<std::unique_ptr<RenderItem>>& getRenderItems() { return mAllRitems; }
    std::unordered_map<std::string, std::unique_ptr<Material>>& getMaterials() { return mMaterials; }
    std::unordered_map<std::string, std::unique_ptr<MeshGeometry>>& getGeometries() { return mGeometries; }

    // Accessor for player aircraft, for gameplay programming.
    Aircraft* getPlayerAircraft() const { return playerAircraft; }
    Aircraft* playerAircraft; // Direct pointer to the player's aircraft for easy access.
};
