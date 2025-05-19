// Put repo content into VSCode

    git clone {HTTPS}

// Add specific (or all) file to later commit and push

    git add {FILE_NAME} (or .)

// Commit changes

    git commit -m "Commit Message"

// Save Changes

    git push origin {BRANCH}

// Sparse Checkout // // Inside of a directory...

// Make directory a git directory

    git init

// Make empty directory with remote git remote add -f origin

// Enable sparse checkout

    git config core.sparseCheckout true

// Choose folders to check out

    echo "dir/ect/ory" >> .git/info/sparse-checkout

// Check out

    git pull origin main
