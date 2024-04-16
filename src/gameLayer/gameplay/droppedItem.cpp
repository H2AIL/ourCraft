#include <gameplay/droppedItem.h>
#include <multyPlayer/serverChunkStorer.h>



void DroppedItem::update(float deltaTime, decltype(chunkGetterSignature) *chunkGetter)
{

	updateForces(deltaTime, true);

	resolveConstrainsAndUpdatePositions(chunkGetter, deltaTime, {0.4,0.4,0.4});


}

void DroppedItemServer::update(float deltaTime, decltype(chunkGetterSignature) *chunkGetter,
	ServerChunkStorer &serverChunkStorer)
{
	entity.update(deltaTime, chunkGetter);
}

void DroppedItemClient::update(float deltaTime, 
	decltype(chunkGetterSignature) *chunkGetter)
{
	entity.update(deltaTime, chunkGetter);
}