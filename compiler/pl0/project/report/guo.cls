\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{guo}

%-----------------------------------------------------------------------------
% Setup
%-----------------------------------------------------------------------------
\LoadClass[a4paper,12pt]{article}

%-----------------------------------------------------------------------------
% Package
%-----------------------------------------------------------------------------
\usepackage{xeCJK}
\usepackage[includefoot]{geometry}

%-----------------------------------------------------------------------------
% Format
%-----------------------------------------------------------------------------

% Fonts
\setmainfont{Times New Roman}
\setsansfont{Arial}
\setmonofont{Courier New}
\setCJKmainfont{AR PL New Sung}
\setCJKsansfont{WenQuanYi Micro Hei}
\setCJKmonofont{Courier New}
\setCJKfamilyfont{song}{AR PL New Sung}
\setCJKfamilyfont{hei}{WenQuanYi Micro Hei}

% Page Layout
\geometry{top=28mm,bottom=15mm,left=30mm,right=20mm,footskip=10mm,nohead}
\pagenumbering{gobble}

%-----------------------------------------------------------------------------
% Macro
%-----------------------------------------------------------------------------

% Font sizings
\newcommand{\fontsong}{\CJKfamily{song}}
\newcommand{\fonthei}{\CJKfamily{hei}}

\newcommand{\fontla}{\fontsize{42bp}{\baselineskip}\selectfont}    % 初号
\newcommand{\fontlb}{\fontsize{36bp}{\baselineskip}\selectfont}    % 小初
\newcommand{\fontlc}{\fontsize{26bp}{\baselineskip}\selectfont}    % 一号
\newcommand{\fontld}{\fontsize{24bp}{\baselineskip}\selectfont}    % 小一
\newcommand{\fontle}{\fontsize{22bp}{\baselineskip}\selectfont}    % 二号
\newcommand{\fontlf}{\fontsize{18bp}{\baselineskip}\selectfont}    % 小二
\newcommand{\fontlg}{\fontsize{16bp}{\baselineskip}\selectfont}    % 三号
\newcommand{\fontli}{\fontsize{15bp}{\baselineskip}\selectfont}    % 小三
\newcommand{\fontlj}{\fontsize{14bp}{\baselineskip}\selectfont}    % 四号
\newcommand{\fontlk}{\fontsize{12bp}{\baselineskip}\selectfont}    % 小四
\newcommand{\fontll}{\fontsize{10.5bp}{\baselineskip}\selectfont}  % 五号
\newcommand{\fontlm}{\fontsize{9bp}{\baselineskip}\selectfont}     % 小五
\newcommand{\fontln}{\fontsize{7.5bp}{\baselineskip}\selectfont}   % 六号
\newcommand{\fontlo}{\fontsize{6.5bp}{\baselineskip}\selectfont}   % 小六
\newcommand{\fontlp}{\fontsize{5.5bp}{\baselineskip}\selectfont}   % 七号
\newcommand{\fontlq}{\fontsize{5bp}{\baselineskip}\selectfont}     % 小七

% Base Line
\renewcommand{\baselinestretch}{1.25}

% Underline
\newcommand\drawunderline[2][6.5cm]{ %
    \hskip1pt\underline{\hb@xt@#1{\hss#2\hss}}\hskip3pt %
}

% Meta
% FIXME control letter \@
\newcommand\paperauthor[1]{\def\paperauthor{#1}}
\newcommand\papertitle[1]{\def\papertitle{#1}}
\newcommand\studentno[1]{\def\studentno{#1}}
\newcommand\supervisor[1]{\def\supervisor{#1}}
\newcommand\colleage[1]{\def\colleage{#1}}
\newcommand\major[1]{\def\major{#1}}
\newcommand\grade[1]{\def\grade{#1}}
\newcommand\class[1]{\def\class{#1}}

\endinput
