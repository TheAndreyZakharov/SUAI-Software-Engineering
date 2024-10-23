import bpy

# Очистка сцены
bpy.ops.object.select_all(action='DESELECT')
bpy.ops.object.select_all(action='SELECT')
bpy.ops.object.delete(use_global=False)

# Добавление плоскости
bpy.ops.mesh.primitive_plane_add(size=10)
plane = bpy.context.object

# Добавление модификатора Subdivision Surface
subsurf_modifier = plane.modifiers.new(name="Subdivision", type='SUBSURF')
subsurf_modifier.levels = 6
subsurf_modifier.render_levels = 6

# Добавление модификатора Displace
displace_modifier = plane.modifiers.new(name="Displace", type='DISPLACE')

# Создание текстуры для Displace
texture = bpy.data.textures.new(name="DisplaceTexture", type='CLOUDS')
texture.noise_scale = 1.0  # Регулировка масштаба текстуры
texture.intensity = 4.0  # Регулировка интенсивности для более выраженных высот и впадин
texture.contrast = 2.0  # Регулировка контраста для резких изменений высот

# Применение текстуры к модификатору Displace
displace_modifier.texture = texture
displace_modifier.strength = 10.0  # Увеличение силы модификатора для более выраженного рельефа

# Создание материала
material = bpy.data.materials.new(name="PlaneMaterial")
material.use_nodes = True
nodes = material.node_tree.nodes
links = material.node_tree.links

# Очистка узлов
for node in nodes:
    nodes.remove(node)

# Добавление узлов
shader_node = nodes.new(type='ShaderNodeBsdfPrincipled')
material_output_node = nodes.new(type='ShaderNodeOutputMaterial')

# Соединение узлов
links.new(shader_node.outputs['BSDF'], material_output_node.inputs['Surface'])

# Применение материала к плоскости
plane.data.materials.append(material)

# Установка масштаба плоскости для создания большого рельефа
plane.scale = (10, 10, 1)

# Создание маски для равнины
bpy.ops.object.mode_set(mode='EDIT')
bpy.ops.mesh.subdivide(number_cuts=50)  # Увеличение количества разбиений
bpy.ops.object.mode_set(mode='OBJECT')

# Добавление материала для маски
bpy.data.objects[plane.name].select_set(True)
bpy.context.view_layer.objects.active = plane
bpy.ops.object.vertex_group_add()
vertex_group = plane.vertex_groups.active
vertex_group.name = "PlainsMask"

# Выделение вершин для маски
for vertex in plane.data.vertices:
    if abs(vertex.co.z) < 1.0:  # Задаем порог для равнины
        vertex_group.add([vertex.index], 1.0, 'REPLACE')
    else:
        vertex_group.add([vertex.index], 0.0, 'REPLACE')

# Применение маски к модификатору Displace
displace_modifier.vertex_group = vertex_group.name

# Добавление освещения и камеры для рендеринга
bpy.ops.object.light_add(type='SUN', location=(10, -10, 10))
bpy.ops.object.camera_add(location=(0, -15, 10))
camera = bpy.context.object
camera.rotation_euler = (1.1, 0, 0)
bpy.context.scene.camera = camera

# Настройка параметров рендеринга
bpy.context.scene.render.resolution_x = 1920
bpy.context.scene.render.resolution_y = 1080
bpy.context.scene.render.resolution_percentage = 100

# Рендеринг сцены
bpy.ops.render.render(write_still=True)