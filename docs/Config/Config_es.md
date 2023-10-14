# Configuracion de Patata Engine con YAML

<i>
Si se escriben los valores en mayuscula o minuscula, el programa los tomara.

Las llaves deben de escribirse tal cual como se indica aqui.

Vease la gramatica de [YAML](https://github.com/yaml/yaml-grammar)

⚠️ Patata Engine aun no es capaz de configurar en tiempo real, debe reiniciar para ver los cambios.
</i>


<hr>

<b>graphics-api</b>

<b>Valores posibles:</b> Vulkan, OpenGL <i>(String)</i>

<b>Descripcion:</b>

<i>Decide la api que el motor usara para renderizar los graficos</i>

```yaml
graphics-api : Vulkan
```

<hr>

<b>vsync</b>

<b>Valores posibles:</b> true o false <i>(Booleano)</i>

<b>Descripcion:</b>

<i>True para activar la sincronizacion vertical o false para desactivar la sincronizacion vertical.

La activacion de la sincronizacion vertical limitara los fotogramas por segundo
</i>

```yaml
vsync : true
```
