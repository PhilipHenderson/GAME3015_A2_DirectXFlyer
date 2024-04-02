#include "Aircraft.hpp"
#include "Game.hpp"
#include "World.hpp"

Aircraft::Aircraft(Type type, Game* game) : Entity(game)
, mType(type)
{
	switch (type)
	{
	case (Eagle):
		mSprite = "Eagle";
		break;
	case (Raptor):
		mSprite = "Raptor";
		break;
	default:
		mSprite = "Eagle";
		break;
	}
}

void Aircraft::updateCurrent(const GameTimer& gt) 
{
	static const float followThreshold = 20.0f;
	static const float patrolSpeed = 0.1f;
	static const float followSpeed = 5.0f;
	static float patrolAngle = 0.0f;
	static bool isFollowing = false;
	static float transitionSpeed = 1.0f;

	XMFLOAT3 playerPosition = game->getPlayerAircraft()->getWorldPosition();
	XMFLOAT3 enemyPosition = getWorldPosition();

	// Initialize movementDirection to zero
	XMVECTOR movementDirection = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

	XMVECTOR dirToPlayer = XMVectorSubtract(XMLoadFloat3(&playerPosition), XMLoadFloat3(&enemyPosition));
	float distanceToPlayer = XMVectorGetX(XMVector3Length(dirToPlayer));

	if (mType == Aircraft::Raptor) 
	{
		if (distanceToPlayer < followThreshold && !isFollowing) 
		{
			isFollowing = true;
		}
		else if (distanceToPlayer >= followThreshold && isFollowing) 
		{
			isFollowing = false;
			// Optionally reset patrolAngle here if needed for smoother transition
		}

		if (isFollowing) 
		{
			dirToPlayer = XMVector3Normalize(dirToPlayer);
			movementDirection = XMVectorScale(dirToPlayer, followSpeed * gt.DeltaTime());
			float newYaw = atan2(XMVectorGetZ(dirToPlayer), XMVectorGetX(dirToPlayer));
			setWorldRotation(0, newYaw, 0);
		}
		else 
		{
			patrolAngle += patrolSpeed * gt.DeltaTime();
			enemyPosition.x = 5.0f * cosf(patrolAngle);
			enemyPosition.z = 5.0f * sinf(patrolAngle);
			// Re-initialize movementDirection for patrolling
			movementDirection = XMVectorSet(cosf(patrolAngle), 0.0f, sinf(patrolAngle), 0.0f);
			setWorldRotation(0, -patrolAngle, 0);
		}

		XMVECTOR newPos = XMVectorAdd(XMLoadFloat3(&enemyPosition), movementDirection);
		XMStoreFloat3(&enemyPosition, newPos);
		setPosition(enemyPosition.x, enemyPosition.y, enemyPosition.z);
	}

	Entity::updateCurrent(gt);
}

void Aircraft::drawCurrent() const
{

	//auto ri = ritems[i];

	//auto vbv = ri->Geo->VertexBufferView();
	//auto ibv = ri->Geo->IndexBufferView();

	//cmdList->IASetVertexBuffers(0, 1, &vbv);
	//cmdList->IASetIndexBuffer(&ibv);
	//cmdList->IASetPrimitiveTopology(ri->PrimitiveType);

	////step18
	//CD3DX12_GPU_DESCRIPTOR_HANDLE tex(mSrvDescriptorHeap->GetGPUDescriptorHandleForHeapStart());
	//tex.Offset(ri->Mat->DiffuseSrvHeapIndex, mCbvSrvDescriptorSize);

	//D3D12_GPU_VIRTUAL_ADDRESS objCBAddress = objectCB->GetGPUVirtualAddress() + ri->ObjCBIndex * objCBByteSize;
	//D3D12_GPU_VIRTUAL_ADDRESS matCBAddress = matCB->GetGPUVirtualAddress() + ri->Mat->MatCBIndex * matCBByteSize;

	////step19
	//cmdList->SetGraphicsRootDescriptorTable(0, tex);
	//cmdList->SetGraphicsRootConstantBufferView(1, objCBAddress);
	//cmdList->SetGraphicsRootConstantBufferView(3, matCBAddress);

	//cmdList->DrawIndexedInstanced(ri->IndexCount, 1, ri->StartIndexLocation, ri->BaseVertexLocation, 0);

}

void Aircraft::buildCurrent()
{
	auto render = std::make_unique<RenderItem>();
	renderer = render.get();
	renderer->World = getTransform();
	XMStoreFloat4x4(&renderer->World, XMMatrixScaling(10.0f, 1.0f, 10.0f));
	renderer->ObjCBIndex = game->getRenderItems().size();
	renderer->Mat = game->getMaterials()[mSprite].get();
	renderer->Geo = game->getGeometries()["boxGeo"].get();
	renderer->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	renderer->IndexCount = renderer->Geo->DrawArgs["box"].IndexCount;
	renderer->StartIndexLocation = renderer->Geo->DrawArgs["box"].StartIndexLocation;
	renderer->BaseVertexLocation = renderer->Geo->DrawArgs["box"].BaseVertexLocation;

	game->getRenderItems().push_back(std::move(render));
}

XMFLOAT3 Aircraft::getForwardVector() const {
	float yaw = mWorldRotation.y;
	return XMFLOAT3(sinf(yaw), 0.0f, cosf(yaw));
}

void Aircraft::moveForward(float dt) {
	// Speed can be a fixed value or based on aircraft characteristics
	float speed = 10.0f; // Example speed value

	// Get the forward vector of the aircraft
	XMFLOAT3 forward = getForwardVector();

	// Update position based on the forward vector and speed
	mPosition.x += forward.x * speed * dt;
	mPosition.y += forward.y * speed * dt;
	mPosition.z += forward.z * speed * dt;

	// Update the aircraft's world position
	setPosition(mPosition.x, mPosition.y, mPosition.z);
}

void Aircraft::moveBackward(float dt) {
	// Speed can be a fixed value or based on aircraft characteristics
	float speed = 10.0f; // Example speed value

	// Get the forward vector of the aircraft
	XMFLOAT3 backward = getForwardVector();

	// Update position based on the forward vector and speed
	mPosition.x -= backward.x * speed * dt;
	mPosition.y -= backward.y * speed * dt;
	mPosition.z -= backward.z * speed * dt;

	// Update the aircraft's world position
	setPosition(mPosition.x, mPosition.y, mPosition.z);
}

void Aircraft::adjustYaw(float amount) {
	// Adjust the yaw and update the aircraft rotation
	float newYaw = getYaw() + amount;
	setWorldRotation(getPitch(), newYaw, getRoll());
}

void Aircraft::adjustPitch(float amount) {
	// Adjust the pitch and update the aircraft rotation
	float newPitch = getPitch() + amount;
	setWorldRotation(newPitch, getYaw(), getRoll());
}

void Aircraft::adjustRoll(float amount) {
	// Adjust the roll and update the aircraft rotation
	float newRoll = getRoll() + amount;
	setWorldRotation(getPitch(), getYaw(), newRoll);
}



