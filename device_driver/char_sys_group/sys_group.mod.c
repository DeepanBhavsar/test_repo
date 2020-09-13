#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xa3ec7281, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x4dc514c7, __VMLINUX_SYMBOL_STR(kobject_put) },
	{ 0xc09b3599, __VMLINUX_SYMBOL_STR(sysfs_create_group) },
	{ 0xe0c4c876, __VMLINUX_SYMBOL_STR(kobject_create_and_add) },
	{ 0x38f83c61, __VMLINUX_SYMBOL_STR(kernel_kobj) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0x20c55ae0, __VMLINUX_SYMBOL_STR(sscanf) },
	{ 0xb4390f9a, __VMLINUX_SYMBOL_STR(mcount) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "0ACD05E441EBE6C032666C1");
