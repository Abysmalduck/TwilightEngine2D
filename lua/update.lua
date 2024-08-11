time = tweng.get_time() * 0.0025;

--print(time)

tweng_scene.object_set_position(1, math.sin(time) * 0.25,math.cos(time) * 0.25,0)
                                --ID --X --Y --Z index
