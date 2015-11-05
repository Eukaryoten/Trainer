// Design revolving around the fact that there is one player that can be followed and controlled

BaseObject obj;

obj.Draw();
mouse.AddControls(obj); // Keeps track of what its controlling
keyboard.AddControls(obj); // Keeps track of what its controlling
camera.Following(obj); // Keeps track of what its controlling