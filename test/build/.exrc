if &cp | set nocp | endif
let s:cpo_save=&cpo
set cpo&vim
inoremap <silent> <Plug>(neocomplcache_start_omni_complete) 
inoremap <silent> <Plug>(neocomplcache_start_auto_complete_no_select) 
inoremap <silent> <Plug>(neocomplcache_start_auto_complete) =neocomplcache#mappings#popup_post()
inoremap <silent> <expr> <Plug>(neocomplcache_start_unite_quick_match) unite#sources#neocomplcache#start_quick_match()
inoremap <silent> <expr> <Plug>(neocomplcache_start_unite_complete) unite#sources#neocomplcache#start_complete()
inoremap <silent> <Plug>NERDCommenterInsert  <BS>:call NERDComment('i', "insert")
nnoremap  :bn
nnoremap <silent>  :CtrlP
nmap ,ca <Plug>NERDCommenterAltDelims
xmap ,cu <Plug>NERDCommenterUncomment
nmap ,cu <Plug>NERDCommenterUncomment
xmap ,cb <Plug>NERDCommenterAlignBoth
nmap ,cb <Plug>NERDCommenterAlignBoth
xmap ,cl <Plug>NERDCommenterAlignLeft
nmap ,cl <Plug>NERDCommenterAlignLeft
nmap ,cA <Plug>NERDCommenterAppend
xmap ,cy <Plug>NERDCommenterYank
nmap ,cy <Plug>NERDCommenterYank
xmap ,cs <Plug>NERDCommenterSexy
nmap ,cs <Plug>NERDCommenterSexy
xmap ,ci <Plug>NERDCommenterInvert
nmap ,ci <Plug>NERDCommenterInvert
nmap ,c$ <Plug>NERDCommenterToEOL
xmap ,cn <Plug>NERDCommenterNested
nmap ,cn <Plug>NERDCommenterNested
xmap ,cm <Plug>NERDCommenterMinimal
nmap ,cm <Plug>NERDCommenterMinimal
xmap ,c  <Plug>NERDCommenterToggle
nmap ,c  <Plug>NERDCommenterToggle
xmap ,cc <Plug>NERDCommenterComment
nmap ,cc <Plug>NERDCommenterComment
nmap ,ihn :IHN
nmap ,is :IHS:A
nmap ,ih :IHS
map P "+p
map Y "+y
vmap ]f :call PythonDec("function", 1)
nmap ]f :call PythonDec("function", 1)
omap ]f :call PythonDec("function", 1)
vmap ]F :call PythonDec("function", -1)
nmap ]F :call PythonDec("function", -1)
omap ]F :call PythonDec("function", -1)
vmap ]j :call PythonDec("class", 1)
nmap ]j :call PythonDec("class", 1)
omap ]j :call PythonDec("class", 1)
vmap ]J :call PythonDec("class", -1)
nmap ]J :call PythonDec("class", -1)
omap ]J :call PythonDec("class", -1)
map ]<Down> :call PythonNextLine(1)
map ]<Up> :call PythonNextLine(-1)
map ]d :call PythonSelectObject("function")
map ]c :call PythonSelectObject("class")
vmap ]u :call PythonUncommentSelection()
nmap ]u :call PythonUncommentSelection()
omap ]u :call PythonUncommentSelection()
vmap ]# :call PythonCommentSelection()
nmap ]# :call PythonCommentSelection()
omap ]# :call PythonCommentSelection()
vmap ]> >
nmap ]> ]tV]e>
omap ]> ]tV]e>
vmap ]< <
nmap ]< ]tV]e<
omap ]< ]tV]e<
map ]v ]tV]e
vmap ]e :PEoBm'gv``
nmap ]e :PEoB
omap ]e :PEoB
vmap ]t :PBOBm'gv``
nmap ]t :PBoB
omap ]t :PBoB
vmap gx <Plug>NetrwBrowseXVis
nmap gx <Plug>NetrwBrowseX
vnoremap <silent> <Plug>NetrwBrowseXVis :call netrw#BrowseXVis()
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#BrowseX(expand((exists("g:netrw_gx")? g:netrw_gx : '<cfile>')),netrw#CheckIfRemote())
xnoremap <silent> <Plug>NERDCommenterUncomment :call NERDComment("x", "Uncomment")
nnoremap <silent> <Plug>NERDCommenterUncomment :call NERDComment("n", "Uncomment")
xnoremap <silent> <Plug>NERDCommenterAlignBoth :call NERDComment("x", "AlignBoth")
nnoremap <silent> <Plug>NERDCommenterAlignBoth :call NERDComment("n", "AlignBoth")
xnoremap <silent> <Plug>NERDCommenterAlignLeft :call NERDComment("x", "AlignLeft")
nnoremap <silent> <Plug>NERDCommenterAlignLeft :call NERDComment("n", "AlignLeft")
nnoremap <silent> <Plug>NERDCommenterAppend :call NERDComment("n", "Append")
xnoremap <silent> <Plug>NERDCommenterYank :call NERDComment("x", "Yank")
nnoremap <silent> <Plug>NERDCommenterYank :call NERDComment("n", "Yank")
xnoremap <silent> <Plug>NERDCommenterSexy :call NERDComment("x", "Sexy")
nnoremap <silent> <Plug>NERDCommenterSexy :call NERDComment("n", "Sexy")
xnoremap <silent> <Plug>NERDCommenterInvert :call NERDComment("x", "Invert")
nnoremap <silent> <Plug>NERDCommenterInvert :call NERDComment("n", "Invert")
nnoremap <silent> <Plug>NERDCommenterToEOL :call NERDComment("n", "ToEOL")
xnoremap <silent> <Plug>NERDCommenterNested :call NERDComment("x", "Nested")
nnoremap <silent> <Plug>NERDCommenterNested :call NERDComment("n", "Nested")
xnoremap <silent> <Plug>NERDCommenterMinimal :call NERDComment("x", "Minimal")
nnoremap <silent> <Plug>NERDCommenterMinimal :call NERDComment("n", "Minimal")
xnoremap <silent> <Plug>NERDCommenterToggle :call NERDComment("x", "Toggle")
nnoremap <silent> <Plug>NERDCommenterToggle :call NERDComment("n", "Toggle")
xnoremap <silent> <Plug>NERDCommenterComment :call NERDComment("x", "Comment")
nnoremap <silent> <Plug>NERDCommenterComment :call NERDComment("n", "Comment")
nmap <F8> :SrcExplToggle 
map <F3> :NERDTreeToggle
imap ,ihn :IHN
imap ,is :IHS:A
imap ,ih :IHS
let &cpo=s:cpo_save
unlet s:cpo_save
set background=dark
set backspace=2
set completefunc=neocomplcache#complete#manual_complete
set completeopt=preview,menuone
set expandtab
set fileencodings=ucs-bom,utf-8,default,latin1
set foldlevelstart=99
set guicursor=n-v-c:hor10
set helplang=cn
set hlsearch
set listchars=trail:+
set printoptions=paper:a4
set ruler
set runtimepath=~/.vim,~/.vim/bundle/Vundle.vim,~/.vim/bundle/scons.vim,~/.vim/bundle/SrcExpl,~/.vim/bundle/vim-racket,~/.vim/bundle/vim-scala,~/.vim/bundle/vim-airline,~/.vim/bundle/vim-airline-themes,~/.vim/bundle/vim-colorschemes,~/.vim/bundle/a.vim,~/.vim/bundle/google.vim,~/.vim/bundle/cpp.vim,~/.vim/bundle/taglist.vim,~/.vim/bundle/python.vim,~/.vim/bundle/vim-template,~/.vim/bundle/nginx.vim,~/.vim/bundle/vim-powerline,~/.vim/bundle/nerdtree,~/.vim/bundle/ctrlp.vim,~/.vim/bundle/nerdcommenter,~/.vim/bundle/neocomplcache.vim,/var/lib/vim/addons,/usr/share/vim/vimfiles,/usr/share/vim/vim74,/usr/share/vim/vimfiles/after,/var/lib/vim/addons/after,~/.vim/after,~/.vim/bundle/Vundle.vim,~/.vim/bundle/Vundle.vim/after,~/.vim/bundle/scons.vim/after,~/.vim/bundle/SrcExpl/after,~/.vim/bundle/vim-racket/after,~/.vim/bundle/vim-scala/after,~/.vim/bundle/vim-airline/after,~/.vim/bundle/vim-airline-themes/after,~/.vim/bundle/vim-colorschemes/after,~/.vim/bundle/a.vim/after,~/.vim/bundle/google.vim/after,~/.vim/bundle/cpp.vim/after,~/.vim/bundle/taglist.vim/after,~/.vim/bundle/python.vim/after,~/.vim/bundle/vim-template/after,~/.vim/bundle/nginx.vim/after,~/.vim/bundle/vim-powerline/after,~/.vim/bundle/nerdtree/after,~/.vim/bundle/ctrlp.vim/after,~/.vim/bundle/nerdcommenter/after,~/.vim/bundle/neocomplcache.vim/after
set shiftwidth=2
set showtabline=2
set suffixes=.bak,~,.swp,.o,.info,.aux,.log,.dvi,.bbl,.blg,.brf,.cb,.ind,.idx,.ilg,.inx,.out,.toc
set noswapfile
set tabline=%!airline#extensions#tabline#get()
set tabstop=2
set tags=tags;/
" vim: set ft=vim :
