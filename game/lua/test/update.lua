

delim = 2 / this_id
speed = 100
time = tweng.get_time()

big_dist_sin = math.sin (time * 0.25 + math.pi/delim) * 0.25
big_dist_cos = math.cos (time * 0.25 + math.pi/delim) * 0.25

tweng_scene.object_set_position(this_id, math.sin(time + math.pi / delim) * 0.5 + big_dist_sin ,math.cos(time + math.pi / delim) * 0.5 + big_dist_cos, -this_id)

tweng_scene.object_set_rotation_euler(this_id,0, time, 0)
