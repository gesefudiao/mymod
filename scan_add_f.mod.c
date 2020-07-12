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
	{ 0x3e7185d2, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xea290159, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x1eb7ab37, __VMLINUX_SYMBOL_STR(filp_close) },
	{ 0xd5bab47f, __VMLINUX_SYMBOL_STR(page_referenced) },
	{ 0x201621f1, __VMLINUX_SYMBOL_STR(pv_mmu_ops) },
	{ 0x3c1498c4, __VMLINUX_SYMBOL_STR(pid_task) },
	{ 0x47779a3, __VMLINUX_SYMBOL_STR(find_get_pid) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0xddaeff80, __VMLINUX_SYMBOL_STR(filp_open) },
	{ 0xdb7305a1, __VMLINUX_SYMBOL_STR(__stack_chk_fail) },
	{ 0xc0075496, __VMLINUX_SYMBOL_STR(vfs_write) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x3356b90b, __VMLINUX_SYMBOL_STR(cpu_tss) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "396416F5BD3CF8A94B88891");
