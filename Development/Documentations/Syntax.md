# Hyper Syntax

## Contents
1. [Example](#example)

## Example
```hyper
struct Node
{
	value: int;
	left: Node*;
	right: Node*;
}

struct BinaryTree
{
	root: Node*;
}

fn (mut BinaryTree) insert(value: int, left: Node*) -> void
{
	if value < leaf.value
	{
		if leaf.left != 0
		{
			self.insert(value, leaf.left);
			return;
		}

		leaf.left = sys.allocate<Node>();
		leaf.left.value = value;
	}
	else
	{
		if leaf.right != 0
		{
			self.insert(value, leaf.right);
			return;
		}

		leaf.right = sys.allocate<Node>();
		leaf.right.value = value;
	}
}

pub fn (mut BinaryTree) insert(value: int) -> void
{
	if self.root != 0
	{
		self.insert(value, self.root);
		return;
	}

	self.root = sys.allocate<Node>();
	self.root.value = value;
}

fn (BinaryTree) search(value: int, leaf: Node*) -> Node*
{
	if leaf == 0
	{
		return 0;
	}

	if leaf.value == value
	{
		return leaf;
	}

	if value < leaf.value
	{
		return self.search(value, leaf.left);
	}

	return self.search(value, leaf.right);
}

pub fn (BinaryTree) search(value: int) -> Node*
{
	self.search(value, self.root);
}

fn main() -> void
{
	binary_tree: mut BinaryTree;
	binary_tree.insert(10);
	binary_tree.insert(6);
	binary_tree.insert(14);
	binary_tree.insert(5);
	binary_tree.insert(8);
	binary_tree.insert(11);
	binary_tree.insert(18);
}
```
