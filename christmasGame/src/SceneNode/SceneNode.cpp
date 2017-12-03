#include "SceneNode.h"


///////////////////////////////////////////////////////////////////////////////////////////////
CSampleSceneNode::CSampleSceneNode(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id)
	: scene::ISceneNode(parent, mgr, id)
{
	Material.Wireframe = false;
	Material.Lighting = false;

	//shape of node
	Vertices[0] = video::S3DVertex(0, 0, 100, 0, 0, 1, video::SColor(255, 0, 0, 255), 0, 0);
	Vertices[1] = video::S3DVertex(10, 0, -10, 1, 0, 0, video::SColor(0, 255, 0, 255), 0, 1);
	Vertices[2] = video::S3DVertex(0, 20, 0, 0, 1, 0, video::SColor(0, 0, 255, 255), 1, 1);
	Vertices[2] = video::S3DVertex(-10, 0, -10, 1, 1, 0, video::SColor(255, 0, 255, 255), 1, 0);
	
	//bounding of node
	Box.reset(Vertices[0].Pos);
	for (s32 i = 1; i < 4; i++)
		Box.addInternalPoint(Vertices[i].Pos);
}

///////////////////////////////////////////////////////////////////////////////////////////////
void CSampleSceneNode::OnRegisterSceneNode()
{
	if (IsVisible)
		SceneManager->registerNodeForRendering(this);
	ISceneNode::OnRegisterSceneNode();
}

///////////////////////////////////////////////////////////////////////////////////////////////
void CSampleSceneNode::render()
{
	u16 indices[] = {0,2,3,  2,1,3,  1,0,3,  2,0,1 };
	video::IVideoDriver* driver = SceneManager->getVideoDriver();

	driver->setMaterial(Material);
	driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
	driver->drawVertexPrimitiveList(&Vertices[0], 4, &indices, 4);
}

