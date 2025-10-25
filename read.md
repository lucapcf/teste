# My Dotfiles (Managed by Ansible)

This repository contains my personal dotfiles and a complete Ansible playbook to set up a new system from scratch.

This playbook automates:

  * Package installation (for Fedora, Debian, and Arch).
  * Installation of `yay` on Arch.
  * Installation of Nerd Fonts.
  * Compiling Suckless tools (`dwm`, `st`, etc.).
  * Deployment of all configurations.

It uses **Ansible** to manage the entire process, including a `rsync`-based task to intelligently sync dotfiles from this repo to the `$HOME` directory, replicating the behavior of GNU Stow.

## 🚀 First-Time Setup on a New Machine

1.  **Install Bootstrap Tools:**
    You must manually install the bare minimum tools: `git` and `ansible`.

      * **Fedora:** `sudo dnf install git ansible-core`
      * **Debian:** `sudo apt install git ansible-core`
      * **Arch:** `sudo pacman -S git ansible-core`

2.  **Clone This Repository:**
    `git clone <your-repo-url> ~/dotfiles`

3.  **Run the Playbook:**
    This one command will run the entire setup.

    ```bash
    cd ~/dotfiles
    ansible-playbook setup.yml
    ```

    Ansible will ask for your `sudo` password to install packages and run privileged tasks.

4.  **Reboot:**
    Once the playbook is finished, reboot your system for all changes to take effect.
    `sudo reboot`

-----

## 🔁 Daily Workflow

This setup uses a **one-way sync** model. Your git repository is the **source of truth.**

> **Important:** You should *always* edit the files inside this `dotfiles` repository (e.g., `~/dotfiles/nvim/.config/nvim/init.vim`).
>
> If you edit the "live" file (e.g., `~/.config/nvim/init.vim`), your changes will be **overwritten** the next time you run the playbook.

The command to deploy all changes is always the same:
`ansible-playbook setup.yml`

-----

### Workflow 1: Edit a File

1.  **Edit:** Make your change to the "master" file inside the local repo.
      * `nano ~/dotfiles/alacritty/.config/alacritty/alacritty.yml`
2.  **Deploy:** Run the Ansible playbook.
      * `ansible-playbook setup.yml`
3.  **(Recommended)** Commit and push your change.
      * `git add .`
      * `git commit -m "Updated alacritty theme"`
      * `git push`

-----

### Workflow 2: Pull Changes from Remote

1.  **Pull:** `cd` to your repo and pull the latest changes.
      * `cd ~/dotfiles`
      * `git pull`
2.  **Deploy:** Run the Ansible playbook.
      * `ansible-playbook setup.yml`

This will automatically apply all pulled changes (edits, creations, and deletions) to your local system.

-----

### Workflow 3: Create or Delete a File

You **do not need to edit the playbook** to add or remove files. The `synchronize` task handles it automatically.

**To Create a New File:**

1.  **Create:** Add the new file *inside the repo*, following the correct directory structure.
      * `touch ~/dotfiles/nvim/.config/nvim/new-plugin.lua`
2.  **Deploy:** Run the Ansible playbook.
      * `ansible-playbook setup.yml`
      * Ansible will automatically see the new file and copy it to `~/.config/nvim/new-plugin.lua`.

**To Delete a File:**

1.  **Delete:** Delete the file *from the repo*.
      * `git rm ~/dotfiles/nvim/.config/nvim/old-plugin.lua`
2.  **Deploy:** Run the Ansible playbook.
      * `ansible-playbook setup.yml`
      * The playbook will see the file is missing from the source and **delete it from your system** (`~/.config/nvim/old-plugin.lua`).

