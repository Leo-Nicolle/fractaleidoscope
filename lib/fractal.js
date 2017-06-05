
const BABYLON = require("babylonjs");

let fractal = {

scene: null,
mesh: null,

createScene : function (engine, canvas) {


    // This creates a basic Babylon Scene object (non-mesh)
    let scene = new BABYLON.Scene(engine);
    fractal.scene = scene;
    // This creates and positions a free camera (non-mesh)
    let camera = new BABYLON.FreeCamera("camera1", new BABYLON.Vector3(0, 5, -10), scene);

    // This targets the camera to scene origin
    camera.setTarget(BABYLON.Vector3.Zero());

    // This attaches the camera to the canvas
    camera.attachControl(canvas, true);

    // This creates a light, aiming 0,1,0 - to the sky (non-mesh)
    let light = new BABYLON.HemisphericLight("light1", new BABYLON.Vector3(0, 1, 0), scene);

    // Default intensity is 1. Let's dim the light a small amount
    light.intensity = 0.7;

    // Our built-in 'sphere' shape. Params: name, subdivs, size, scene
    let mesh = CreatePlane("mesh", 10, scene, false, BABYLON.Mesh.FRONTSIDE); 
    mesh.material.diffuseTexture = new BABYLON.VideoTexture.CreateFromWebCam(scene, function(videoTexture) {},
     { maxWidth: 256, maxHeight: 256 });  
    fractal.mesh = mesh;

    return scene;

},


run: function() {

	const canvas = document.getElementById("canvas");

    var engine = new BABYLON.Engine(canvas, true);
    // var scene = new BABYLON.Scene(engine);

	var scene = fractal.createScene(engine, canvas);
     engine.runRenderLoop(function() {
        scene.render();
        // displayPaths(canvas2d);
       
      });

}

};

module.exports = fractal;