#!/bin/bash
# LazyA Uninstallation Script

echo "  Uninstalling LazyA..."
echo ""

# 1. Remove binary from system
if [ -f /usr/local/bin/lazy ]; then
    echo " Removing /usr/local/bin/lazy..."
    sudo rm -f /usr/local/bin/lazy
    echo "[OK] Removed"
else
    echo "[WARN] /usr/local/bin/lazy not found"
fi

# 2. Remove ~/.lazya directory if it exists
if [ -d ~/.lazya ]; then
    echo " Removing ~/.lazya..."
    rm -rf ~/.lazya
    echo "[OK] Removed"
else
    echo "[WARN] ~/.lazya not found"
fi

# 3. Clean up shell config references
for rc_file in ~/.bashrc ~/.zshrc ~/.profile ~/.config/fish/config.fish; do
    if [ -f "$rc_file" ]; then
        if grep -q "LAZYA" "$rc_file" 2>/dev/null; then
            echo " Cleaning $rc_file..."
            # Create backup
            cp "$rc_file" "${rc_file}.backup"
            
            # Using sed to delete lines matching LazyA configuration
            # Deletes from "# LazyA Configuration" line and the next 2 lines
            if [[ "$rc_file" == *"fish"* ]]; then
                 # Fish syntax might be different, simple grep -v for now or just warn
                 # Attempting simple sed for set -gx LAZYA_HOME
                 sed -i '/set -gx LAZYA_HOME/d' "$rc_file"
                 sed -i '/set -gx PATH \$LAZYA_HOME/d' "$rc_file"
            else
                 sed -i '/# LazyA/,+2d' "$rc_file"
                 sed -i '/LAZYA_HOME/d' "$rc_file"
            fi
            
            echo "[OK] Cleaned (backup saved to ${rc_file}.backup)"
        fi
    fi
done

# 4. Clean old build directory if it exists
if [ -d build ]; then
    echo " Cleaning old build directory..."
    rm -rf build
    echo "[OK] Removed"
fi

echo ""
echo "[OK] Uninstallation complete!"
echo ""
