print("HELLO GUYS")

time = 0;

test_id1 = tweng_scene.add_object("test", "sprite", "../game/resources/textures/default.png")
test_id2 = tweng_scene.add_object("test", "sprite", "../game/resources/textures/default.png")
test_id3 = tweng_scene.add_object("test", "sprite", "../game/resources/textures/default.png")

print(test_id1)
print(test_id2)
print(test_id3)

dofile("../game/lua/another_script.lua")
