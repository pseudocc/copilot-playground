# NOTHING

Just want to test the functionality of the GitHub Copilot.

Codes are not corrected line by line, and it will segfault LUL.

## General Idea

Quite a useful tool, neat code, but makes mistake sometimes.

| Documenting | Code Completion |
|:------------|:----------------|
|    8/10     |       9/10      |

## Misc

### Problem

My `<Tab>` key is mapped to nvim-cmp functionalities, and it may fallback when the cmp context
menu is not availiable. But copilot plugin has no idea about that, and it will fail to enable
itself with it's default settings.

### Solutiuon

My Neovim settings for Github Copilot:
[commit](https://github.com/pseudocc/dotfiles/commit/d0d2824ea9c6a0a36d12994b7eceb7cfa469d014)
