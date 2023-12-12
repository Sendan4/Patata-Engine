# Configuration of Patata Engine with YAML

<i>
If you write the values in upper or lower case, the program will take them.

The keys must be written as indicated here.

See the [YAML](https://github.com/yaml/yaml-grammar) grammar

⚠️ Patata Engine is not yet able to configure in real time, you must restart to see the changes.
</i>


<hr>

<b>graphics-api</b>

<b>Possible values:</b> Vulkan, OpenGL <i>(String)</i>

<b>Description:</b>

<i>Decide the api that the engine will use to render the graphics.</i>

```yaml
graphics-api : Vulkan
```

<hr>

<b>vsync</b>

<b>Possible values:</b> true o false <i>(Boolean)</i>

<b>Description:</b>

<i>True to activate vertical synchronization or false to deactivate vertical synchronization.

Activating vertical sync will limit the frames per second.
</i>

```yaml
vsync : true
```
