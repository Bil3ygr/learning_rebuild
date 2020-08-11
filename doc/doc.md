****# 学习记录

## 读取PNG图片失败问题

在读取图片时，需要判断图片的`nrChannels`，根据`nrChannels`确定**colorType**，并在调用`glTexImage2D`时，
将**colorType**传入，这样才能正确读取资源到贴图

## 设置shader的uniform sampler2D无效

`glActiveTexture`和`uniform sampler2D`的值不是同一个，`GL_TEXTURE0`的实际值为3w+，
而uniform里需要的则是0、1、2等，因此在设置Int时需要给指定的值，而不能用`GL_TEXTURE0`这些枚举值

## 项目配置（废弃）

根据**配置**和**平台**的不同，每种组合都要对一下内容进行设置，否则可能会出现找不到目录、链接失败等问题

1. **属性**->**VC++目录**->**包含目录**/**库目录**，通常是相对路径`$(SolutionDir)\xxx`，意思是解决方案（工程）目录下的`xxx`文件夹，包含目录为`Include`，库目录为`Lib`
> 也可以是本地绝对路径，不过为了到任意机器都能使用，建议还是用相对路径
2. **属性**->**链接器**->**输入**->**附加依赖项**，需要添加`Lib`目录下的lib文件
3. 可能会出现找不到`VCRUNTIME140_1D.dll`的问题，下载一个放入exe执行目录即可，目前使用**生成后事件**的方式，在生成后调用bat，将缺少的dll复制到生成目录

> **目前使用CMake生成项目，以上这些配置都在CMake中处理完毕，一般来说不需要手动处理**

## 清理Scene后屏幕闪烁

这是因为用了双缓冲的机制，如果glClear是在Scene被delete时调用，那么只会影响当前的缓冲，
而另外一个里还是之前绘制的内容，导致`glfwSwapBuffers`时同时绘制之前的内容和空白页，
看起来就像是疯狂闪烁。

实际上在绘制时，每一帧都应该进行`glClear`的操作，在所有绘制前清理屏幕，再进行绘制。
而由于默认的屏幕本来就是黑色，不进行`glClear`操作也不会有问题。

最终的解决方案为，在主循环中，在scenemgr进行update时，判断当前是否有场景，
如果没有场景则使用默认的`glClear`进行清理，保证显示正确。

## CMake

简单描述部分指令内容，所有`xxx`、`yyy`均为变量名，可任意替换；带`...`说明可以任意数量，用空格隔开

|命令|描述|
|-|-|
|`set(VAR_NAME xxx...)`|设置变量名，后续通过`${VARNAME}`进行使用|
|`include_directories(xxx...)`|包含目录，会设置**属性**->**C/C++**->**附加包含目录**，效果等同**VC++目录**->**包含目录**|
|`link_directories(xxx...)`|库目录，会设置**属性**->**链接器**->**附加库目录**，效果等同**VC++目录**->**库目录**|
|`add_executable(xxx yyy...)`|设置项目名(xxx)和生成项目所需的文件(yyy...)|
|`target_link_libraries(xxx yyy...)`|设置项目(xxx)的依赖项(yyy...)，会设置**属性**->**链接器**->**输入**->**附加依赖项**|
|`set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT xxx)`|设置启动项，需要CMake3.6版本及以上|
